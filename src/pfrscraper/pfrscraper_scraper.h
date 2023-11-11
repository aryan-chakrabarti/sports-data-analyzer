#ifndef INCLUDE_PFRSCRAPER
#define INCLUDE_PFRSCRAPER

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "pfrscraper_data_table.h"

namespace pfrscraper {

class Scraper {
    template <class T, class U>
    using KeyValueMap = std::unordered_map<T, U>;

    /**
     * Contains the list of players and their respective IDs.
    */
    inline static KeyValueMap<std::string, std::string> s_playerIdMap = {};

    std::string generatePlayerUrl(const std::string& playerId);
    int getResponseString(std::string& output, const std::string& requestUrl);
    int parsePlayerListString(KeyValueMap<std::string, std::string>& output,
                              const std::string& playerListString);
    int getPlayerList(KeyValueMap<std::string, std::string>& output);
    int getPlayerPage(std::string& output, const std::string& playerId);
    int getPlayerId(std::string& output, const std::string& playerName);
    int scrapeData(DataTableMap<std::string>& output,
                   const std::string& htmlResponse);

   public:
    Scraper() noexcept(false);

    /**
     * Retrieves player data and returns as a KeyValueMap (map of strings).
     * If data is invalid, output is an empty map.
     * @returns Player data as a KeyValueMap, empty if invalid.
    */
    std::shared_ptr<DataTableMap<std::string>> getPlayerData(
        const std::string& playerName);
};

}  // namespace pfrscraper
#endif