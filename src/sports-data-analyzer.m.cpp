#include <iostream>
#include "pfrscraper_scraper.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    while (true) {
        std::string player;
        std::cout << "Enter a player's name (type 'q' to quit): ";
        std::getline(std::cin, player);
        if (player == "q") {
            break;
        }
        pfrscraper::Scraper scraper;
        std::string playerList(scraper.getPlayerData(player));
        if (playerList != "") {
            std::cout << "Got the data for " << player << "."
                      << "\n";
        }
    }
    std::cout << std::endl;
    return 0;
}