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

void printTable(const pfrscraper::DataTable<std::string>& table) {
    auto rows = table.rows();
    bool printedCols(false);
    for (auto row(rows.begin()); row != rows.end(); row++) {
        if (!printedCols) {
            std::cout << "\t\t\t";
            std::for_each(
                row->second->begin(), row->second->end(),
                [](auto& elem) { std::cout << "\t\t" << elem.first; });
            std::cout << "\n";
            printedCols = true;
        }
        std::cout << row->first;
        std::for_each(row->second->begin(), row->second->end(), [](auto& elem) {
            std::cout << "\t\t\t\t" << elem.second;
        });
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void processCommand(const std::string& command, PlayerData& data) {
    std::vector<std::string> parsedArgs;
    boost::split(parsedArgs, command, boost::is_any_of("\t "));
    if (parsedArgs.size() == 0) {
        return;
    }
    std::string function(parsedArgs.at(0));
    boost::to_lower(function);
    if (function == "help" || function == "h") {
        std::cout << "Functions:\n\nLOAD [Player Name]: Loads the player with "
                     "name [Player Name] into the current terminal. Make sure "
                     "you specify both first and last name.\n\nSHOW: Shows all "
                     "tables of data associated with the player loaded.\n\nGET "
                     "[Table Name]: Gets the table with name 'Table Name'. "
                     "This name can be found with the 'SHOW' function.\n";
    } else if (function == "load") {
        std::string joinedArgs(boost::algorithm::join(
            std::vector<std::string>(parsedArgs.begin() + 1, parsedArgs.end()),
            " "));
        PlayerData playerInfo(processPlayer(joinedArgs));
        if (playerInfo != nullptr && !playerInfo->map().empty()) {
            data = playerInfo;
        }
    } else if (function == "show") {
        if (data == nullptr || data->map().empty()) {
            std::cerr << "Cannot show data, no player currently loaded."
                      << std::endl;
            return;
        }
        std::for_each(
            data->map().begin(), data->map().end(),
            [](auto& datapair) { std::cout << datapair.first << "\n"; });
    } else if (function == "get") {
        if (data == nullptr || data->map().empty()) {
            std::cerr << "Cannot show data, no player currently loaded."
                      << std::endl;
            return;
        }
        if (parsedArgs.size() != 2) {
            std::cerr << "Please select only one table to show." << std::endl;
            return;
        }
        const auto& dataTable(data->map().find(parsedArgs.at(1)));
        if (dataTable == data->map().end()) {
            std::cerr << "Could not find data table with name "
                      << parsedArgs.at(1) << std::endl;
            return;
        }
        printTable(dataTable->second);
    } else {
        std::cerr << "ERROR: Invalid command. Please try again." << std::endl;
    }
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
               "'LOAD' command to load a player's info.\nType 'HELP' for help, "
               "'q' to quit.\n";
        PlayerData data;
        while (true) {
            std::string command;
            std::cout << "> ";
            std::getline(std::cin, command);
            boost::algorithm::trim(command);
            if (command == "q") {
                break;
            }
            processCommand(command, data);
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