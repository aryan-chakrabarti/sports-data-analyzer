#include <iostream>
#include "pfrscraper_scraper.h"

std::string getPlayerData(const std::string& player) {
    pfrscraper::Scraper scraper;
    return scraper.getPlayerData(player);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            std::string playerList(getPlayerData(argv[i]));
            if (playerList != "") {
                std::cout << "Got the data for " << argv[i] << "."
                          << "\n";
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
        std::string playerList(getPlayerData(player));
        if (playerList != "") {
            std::cout << "Got the data for " << player << "."
                      << "\n";
        }
    }

    std::cout << std::endl;

    return 0;
}