#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include "pfrscraper_scraper.h"
#include "pfrscraper_utils.h"

typedef std::shared_ptr<pfrscraper::DataTableMap<std::string>> PlayerData;

PlayerData getPlayerData(const std::string& player) {
    pfrscraper::Scraper scraper;
    return scraper.getPlayerData(player);
}

PlayerData processPlayer(const std::string& player) {
    std::string properName(pfrscraper::to_proper(player));
    std::cout << "Getting data for " << properName << "...\n\n";
    PlayerData playerData(getPlayerData(player));
    if (!playerData->map().empty()) {
        std::cout << "Successfully loaded data for " << properName << "\n";
    } else {
        std::cerr << "ERROR: Failed to load data for " << properName
                  << std::endl;
    }
    return playerData;
}

void printTable(const pfrscraper::DataTable<std::string>& table,
                bool rowMode = true) {
    auto rows = table.rows();
    if (rowMode) {
        for (auto row(rows.begin()); row != rows.end(); row++) {
            std::cout << row->first << "\n";
            std::for_each(row->second->begin(), row->second->end(),
                          [](auto& elem) {
                              std::cout << "\t" << elem.first << ": "
                                        << elem.second << "\n";
                          });
            std::cout << "\n";
        }
    } else {
        for (size_t col(0); col != table.table().at(0)->size(); col++) {
            bool printedCol(false);
            for (auto row(rows.begin()); row != rows.end(); row++) {
                if (!printedCol) {
                    std::cout << row->second->at(col).first << ":\n";
                    printedCol = true;
                }
                std::cout << "\t" << row->first << "\t\t"
                          << row->second->at(col).second << "\n";
            }
        }
    }
}

std::string removeExtraWhitespace(const std::string& str) {
    bool lastWasSpace(true);
    std::ostringstream output;
    for (const auto& c : str) {
        if (c == ' ' || c == '\t') {
            if (!lastWasSpace) {
                output << ' ';
            }
            lastWasSpace = true;
        } else {
            output << c;
            lastWasSpace = false;
        }
    }
    return output.str();
}

void processCommand(const std::string& command,
                    std::pair<std::string, PlayerData>& player) {
    std::string cleanedCommand(removeExtraWhitespace(command));
    PlayerData& data(player.second);
    std::string& playerName(player.first);
    boost::to_lower(cleanedCommand);
    std::vector<std::string> parsedArgs;
    boost::split(parsedArgs, cleanedCommand, boost::is_any_of(" "));
    if (parsedArgs.size() == 0) {
        return;
    }
    std::string function(parsedArgs.at(0));
    if (function == "help" || function == "h") {
        std::cout
            << "Functions:\n\nLOAD [Player Name]: Loads the player with "
               "name [Player Name] into the current terminal. Make sure "
               "you specify both first and last name.\n\nSHOW: Shows all "
               "tables of data associated with the player loaded.\n\nGET "
               "[Table Name] [View Option = ROW]: Gets the table with name "
               "'Table Name'. "
               "This name can be found with the 'SHOW' function. Optionally "
               "select whether to see the datapoints categorized by ROW (shows "
               "stats for a specific point in time) or "
               "COL (shows one stat over a period of time). Default is by row "
               "(ROW).\n";
    } else if (function == "load") {
        if (parsedArgs.size() < 3) {
            std::cerr << "Please enter a player's first and last name."
                      << std::endl;
            return;
        }
        std::string joinedArgs(boost::algorithm::join(
            std::vector<std::string>(parsedArgs.begin() + 1, parsedArgs.end()),
            " "));
        PlayerData playerInfo(processPlayer(joinedArgs));
        if (playerInfo != nullptr && !playerInfo->map().empty()) {
            data = playerInfo;
            playerName = pfrscraper::to_proper(joinedArgs);
        }
    } else if (function == "show") {
        if (data == nullptr || data->map().empty()) {
            std::cerr << "Cannot show data, no player currently loaded."
                      << std::endl;
            return;
        }
        std::cout << "\nShowing tables for " << playerName << ":\n\n";
        std::for_each(
            data->map().begin(), data->map().end(),
            [](auto& datapair) { std::cout << datapair.first << "\n"; });
    } else if (function == "get") {
        if (data == nullptr || data->map().empty()) {
            std::cerr << "Cannot show data, no player currently loaded."
                      << std::endl;
            return;
        }
        if (parsedArgs.size() == 2) {
            const auto& dataTable(data->map().find(parsedArgs.at(1)));
            if (dataTable == data->map().end()) {
                std::cerr << "Could not find data table with name "
                          << parsedArgs.at(1) << std::endl;
                return;
            }
            printTable(dataTable->second);
        } else if (parsedArgs.size() == 3) {
            bool rowMode(true);
            if (parsedArgs.at(2) == "col") {
                rowMode = false;
            } else if (parsedArgs.at(2) != "row") {
                std::cerr << "Invalid view selection. Please choose "
                             "either ROW to categorize data by time or COL by "
                             "stat over time."
                          << std::endl;
                return;
            }
            const auto& dataTable(data->map().find(parsedArgs.at(1)));
            if (dataTable == data->map().end()) {
                std::cerr << "Could not find data table with name "
                          << parsedArgs.at(1) << std::endl;
                return;
            }
            printTable(dataTable->second, rowMode);
        } else {
            std::cerr
                << "Invalid number of arguments. Please enter a table "
                   "name then optionally ROW if you want to see it "
                   "organized by time period, or COL for each stat over time."
                << std::endl;
            return;
        }

    } else {
        std::cerr << "ERROR: Invalid command. Please try again." << std::endl;
        return;
    }
    std::cout << "\n";
}

int main(int argc, char** argv) {
    if (argc == 2) {
        // We expect a file input
        std::ifstream file(argv[1]);
        if (file.fail()) {
            std::cerr << "Failed to open file " << argv[1] << std::endl;
            return 1;
        }
        std::string player;
        while (std::getline(file, player)) {
            processPlayer(player);
        }
        std::cout << std::endl;
        return 0;
    } else if (argc == 1) {
        std::cout
            << "Welcome to the football player data analyzer.\nStart with the "
               "'LOAD' command to load a player's info.\nType 'HELP' or 'h' "
               "for help, "
               "'q' to quit.\n";
        PlayerData data;
        std::string playerName;
        std::pair<std::string, PlayerData> player(playerName, data);
        while (true) {
            std::string command;
            std::cout << "> ";
            std::getline(std::cin, command);
            boost::algorithm::trim(command);
            if (command == "q") {
                break;
            }
            processCommand(command, player);
        }

        std::cout << std::endl;

        return 0;
    } else {
        std::cerr << "Invalid number of arguments. Please either enter none to "
                     "launch the interactive terminal, or enter a file name to "
                     "process each player line by line."
                  << std::endl;
    }
}