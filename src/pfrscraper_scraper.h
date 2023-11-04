#ifndef INCLUDE_PFRSCRAPER
#define INCLUDE_PFRSCRAPER

#include <string>

namespace pfrscraper {

class Scraper {

    std::string m_playerName;

   public:
    std::string getPlayerData(const std::string& playerName);
};

}  // namespace pfrscraper
#endif