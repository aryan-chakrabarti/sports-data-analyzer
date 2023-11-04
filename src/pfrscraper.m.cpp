#include <iostream>
#include "pfrscraper_scraper.h"

int main(int argc, char** argv) {
    pfrscraper::Scraper scraper("Calais Campbell");
    std::string playerList(scraper.getPlayerData());
    std::cout << playerList << "\nThis is the list of players." << std::endl;
    return 0;
}