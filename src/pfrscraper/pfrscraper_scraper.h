#ifndef INCLUDE_PFRSCRAPER
#define INCLUDE_PFRSCRAPER

#include <string>
#include <unordered_map>

namespace pfrscraper {

typedef std::unordered_map<std::string, std::string> KeyValueMap;

class Scraper {

    /**
     * Contains the list of players and their respective IDs.
    */
    inline static KeyValueMap s_playerIdMap = {};

    std::string generatePlayerUrl(const std::string& playerId);
    int getResponseString(std::string* output, const std::string& requestUrl);
    int parsePlayerListString(KeyValueMap* output,
                              const std::string& playerListString);
    int getPlayerList(KeyValueMap* output);
    int getPlayerPage(std::string* output, const std::string& playerId);
    int getPlayerId(std::string* output, const std::string& playerName);
    int scrapeData(KeyValueMap* output, const std::string& htmlResponse);

   public:
    Scraper() noexcept(false);

    /**
     * Retrieves player data and returns as a KeyValueMap (map of strings).
     * If data is invalid, output is an empty map.
     * @returns Player data as a KeyValueMap, empty if invalid.
    */
    KeyValueMap getPlayerData(const std::string& playerName);
};

}  // namespace pfrscraper
#endif