#include <iostream>
#include "pfrscraper_scraper.h"
#include "pfrscraper_utils.h"

pfrscraper::KeyValueMap getPlayerData(const std::string& player) {
    pfrscraper::Scraper scraper;
    return scraper.getPlayerData(player);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            std::cout << "Getting data for " << pfrscraper::to_proper(argv[i])
                      << ":\n\n";
            pfrscraper::KeyValueMap playerData(getPlayerData(argv[i]));
            if (!playerData.empty()) {
                for (auto iter(playerData.begin()); iter != playerData.end();
                     iter++) {
                    std::cout << "Found data for " << iter->first << ":\n";
                    std::cout << iter->second << "\n\n";
                }
            }
        }
        std::cout << std::endl;
        return 0;
    }

    while (true) {
        std::string player;
        std::cout << "Enter a player's name (type 'q' to quit): ";
        std::getline(std::cin, player);
        if (player == "q") {
            break;
        }
        std::cout << "Getting data for " << pfrscraper::to_proper(player)
                  << ":\n\n";
        pfrscraper::KeyValueMap playerData(getPlayerData(player));
        if (!playerData.empty()) {
            for (auto iter(playerData.begin()); iter != playerData.end();
                 iter++) {
                std::cout << "Found data for " << iter->first << ":\n";
                std::cout << iter->second << "\n\n";
            }
        }
    }

    std::cout << std::endl;

    return 0;
}