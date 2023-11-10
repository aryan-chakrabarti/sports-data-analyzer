#include <fstream>
#include <iostream>
#include "pfrscraper_scraper.h"
#include "pfrscraper_utils.h"

pfrscraper::KeyValueMap getPlayerData(const std::string& player) {
    pfrscraper::Scraper scraper;
    return scraper.getPlayerData(player);
}

void processPlayer(const std::string& player) {
    std::cout << "Getting data for " << pfrscraper::to_proper(player)
              << ":\n\n";
    pfrscraper::KeyValueMap playerData(getPlayerData(player));
    if (!playerData.empty()) {
        for (auto iter(playerData.begin()); iter != playerData.end(); iter++) {
            std::cout << "Found data for " << iter->first << ":\n";
            std::cout << iter->second << "\n\n";
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