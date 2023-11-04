#include <iostream>
#include "pfrscraper_scraper.h"

int main(int argc, char** argv) {
    pfrscraper::Scraper scraper;
    std::string playerList(scraper.getPlayerData("Calais Campbell"));
    std::cout << playerList << "\nThis is the list of players." << std::endl;
    return 0;
}