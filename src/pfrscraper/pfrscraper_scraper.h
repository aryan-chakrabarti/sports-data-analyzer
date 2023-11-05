#ifndef INCLUDE_PFRSCRAPER
#define INCLUDE_PFRSCRAPER

#include <string>
#include <unordered_map>

namespace pfrscraper {

class Scraper {

    typedef std::unordered_map<std::string, std::string> PlayerIdMap;

    /**
     * Contains the list of players and their respective IDs.
    */
    inline static PlayerIdMap s_playerIdMap = {};

    std::string generatePlayerUrl(const std::string& playerId);
    int getResponseString(std::string* output, const std::string& requestUrl);
    int parsePlayerListString(PlayerIdMap* output,
                              const std::string& playerListString);
    int getPlayerList(PlayerIdMap* output);
    int getPlayerPage(std::string* output, const std::string& playerId);
    int getPlayerId(std::string* output, const std::string& playerName);
    int scrapeData(std::string* output, const std::string& htmlResponse);

   public:
    Scraper() noexcept(false);

    /**
     * Retrieves player data and returns as a string.
     * If data is invalid, output is an empty string.
     * @returns player data as a string, empty if invalid.
    */
    std::string getPlayerData(const std::string& playerName);
};

}  // namespace pfrscraper
#endif