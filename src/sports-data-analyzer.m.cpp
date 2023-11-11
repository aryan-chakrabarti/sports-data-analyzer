#include <fstream>
#include <iostream>
#include <memory>
#include "pfrscraper_scraper.h"
#include "pfrscraper_utils.h"

std::shared_ptr<pfrscraper::DataTableMap<std::string>> getPlayerData(
    const std::string& player) {
    pfrscraper::Scraper scraper;
    return scraper.getPlayerData(player);
}

void processPlayer(const std::string& player) {
    typedef pfrscraper::DataTableMap<std::string> TableMap;
    std::string properName(pfrscraper::to_proper(player));
    std::cout << "Getting data for " << properName << ":\n\n";
    std::shared_ptr<TableMap> playerData(getPlayerData(player));
    if (!playerData->map().empty()) {
        std::cout << "Found data for " << properName << ":\n\n";
        for (auto elem(playerData->map().begin());
             elem != playerData->map().end(); elem++) {
            std::cout << elem->second.name() << ":\n";
            for (auto row : elem->second.rows()) {
                std::cout << "\t" << row.first << ":\n";
                for (auto col : elem->second.columns()) {
                    std::cout << "\t\t" << col.first << ": "
                              << *col.second.at(0) << "\n";
                }
            }
        }
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
        while (true) {
            std::string player;
            std::cout << "Enter a player's name (type 'q' to quit): ";
            std::getline(std::cin, player);
            if (player == "q") {
                break;
            }
            processPlayer(player);
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