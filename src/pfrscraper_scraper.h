#ifndef INCLUDE_PFRSCRAPER
#define INCLUDE_PFRSCRAPER

#include <string>

namespace pfrscraper {

class Scraper {

    std::string m_playerName;

   public:
    Scraper(const std::string& playerName);
    Scraper(const Scraper& scraper);
    std::string getPlayerData();
    const std::string& playerName() const;
    std::string& playerName();
    ~Scraper();
};

}  // namespace pfrscraper
#endif