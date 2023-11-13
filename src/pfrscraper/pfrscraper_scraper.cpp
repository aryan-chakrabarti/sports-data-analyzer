#include "pfrscraper_scraper.h"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "boost/algorithm/string.hpp"
#include "html/html_parse.h"
#include "html/html_serialize.h"
#include "pfrscraper_utils.h"

namespace pfrscraper {

/**
 * Generates the url to retrieve the player's HTML page associated
 * with the player ID.
 * @param playerId The ID associated with the player
 * @returns The url of the HTML page with the player's data. If
 * playerId is empty, it returns an empty string.
*/
std::string Scraper::generatePlayerUrl(const std::string& playerId) {
    if (playerId.size() == 0) {
        return "";
    }
    std::ostringstream sstream;
    const std::string YEAR("2023");
    sstream << "https://www.pro-football-reference.com/players/"
            << playerId.at(0) << "/" << playerId << ".htm";
    std::cout << "Going to: " << sstream.str() << "\n";
    return sstream.str();
}

/**
 * Makes a request to the given url, and puts the result in output.
 * @param output The destination of the curl response.
 * @param requestUrl The url to get the data from.
 * @returns 0 if successful, 1 otherwise. Will set output to an empty
 *  string on failure.
*/
int Scraper::getResponseString(std::string& output,
                               const std::string& requestUrl) {
    std::ostringstream response;
    try {
        // That's all that is needed to do cleanup of used resources (RAII style).
        curlpp::Cleanup cleanup;

        // Our request to be sent.
        curlpp::Easy request;

        // Set the URL.
        request.setOpt<curlpp::options::Url>(requestUrl);

        // Set output to playerList string.
        request.setOpt<curlpp::options::WriteStream>(&response);

        // Send request and get a result.
        request.perform();

        output = response.str();

        return 0;
    }

    catch (curlpp::RuntimeError& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        output = "";
        return 1;
    }

    catch (curlpp::LogicError& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        output = "";
        return 1;
    }
}

int Scraper::parsePlayerListString(
    KeyValueMap<std::string, std::string>& output,
    const std::string& playerListString) {
    std::istringstream stream(playerListString);
    while (stream.good()) {
        std::string id;
        std::getline(stream, id, ',');
        std::string name;
        std::getline(stream, name, ',');
        std::string rest;
        std::getline(stream, rest);
        boost::to_upper(name);
        output.insert(std::pair<std::string, std::string>(name, id));
    }
    return 0;
}

/**
 * Gets the map of players with their associated ids.
 * @param output The destination where to store our map
 * @returns 0 if successful, 1 otherwise. If 1, output
 * remains untouched.
*/
int Scraper::getPlayerList(KeyValueMap<std::string, std::string>& output) {
    const std::string requestUrl(
        "https://www.pro-football-reference.com/short/inc/"
        "players_search_list.csv");
    std::string strResponse;
    int rc(getResponseString(strResponse, requestUrl));
    if (rc) {
        std::cerr << "ERROR: Failed to get player list" << std::endl;
        return 1;
    }
    rc = parsePlayerListString(output, strResponse);
    if (rc) {
        std::cerr << "ERROR: Failed to parse player list" << std::endl;
        return 1;
    }
    return 0;
}

/**
 * Retrieves the HTML page of the player associated with playerId.
 * @param output The destination where to store the HTML page
 * @param playerId The player ID to get the page of
 * @returns 0 if successful, 1 otherwise. If 1, output is an empty
 * string.
*/
int Scraper::getPlayerPage(std::string& output, const std::string& playerId) {
    const std::string url(generatePlayerUrl(playerId));
    int rc(getResponseString(output, url));
    if (rc) {
        std::cerr << "ERROR: Failed to get player page for " << playerId
                  << std::endl;
        return 1;
    }
    return 0;
}

/**
 * Gets the player id of the player name. The player's name must be exact,
 * but capitalization doesn't matter.
 * @param output The destination where to store our player ID
 * @param playerName The player name to look up
 * @returns 0 if successful, 1 otherwise
*/
int Scraper::getPlayerId(std::string& output, const std::string& playerName) {
    std::string playerNameUpper(boost::to_upper_copy(playerName));
    auto pair(s_playerIdMap.find(playerNameUpper));
    if (pair == s_playerIdMap.end()) {
        std::cerr << "ERROR: Failed to find player ID for name " << playerName
                  << std::endl;
        return 1;
    }
    output = pair->second;
    return 0;
}

int scrapeTable(DataTable<std::string>& output, const html::Element& table) {
    html::Collection captions(html::getElementsByTag(table, "caption"));
    std::string caption;
    if (captions.length() > 0) {
        caption = captions.get(0).getText();
    } else {
        std::cerr << "ERROR: Failed to find caption for table" << std::endl;
        return 1;
    }
    output.setName(caption);
    html::Element body(html::getElementsByTag(table, "tbody").get(0));
    html::Collection tableRows(html::getElementsByClass(body, "full_table"));
    if (tableRows.length() == 0) {
        std::cerr << "WARNING: Failed to find rows for table \"" << caption
                  << "\" by class. Trying by tag..." << std::endl;
        tableRows = html::getElementsByTag(body, "tr");
        if (tableRows.length() == 0) {
            std::cerr << "ERROR: Failed to find rows for table \"" << caption
                      << "\" by tag. " << std::endl;
            return 1;
        }
    }
    for (size_t i = 0; i < tableRows.length(); i++) {
        html::Element row(tableRows.get(i));
        html::Collection columns(html::getElementsByTag(row, "td"));
        std::vector<std::pair<std::string, std::string>> dataRow;
        for (size_t j = 0; j < columns.length(); j++) {
            html::Element col(columns.get(j));
            std::string dataStat(col.getAttribute("data-stat"));
            std::string dataValue(col.getText());
            dataRow.emplace_back(
                std::pair<std::string, std::string>(dataStat, dataValue));
        }
        std::string rowName;
        auto attributes(row.getAttributes());
        for (auto attr : attributes) {
            if (attr.first == "id") {
                rowName = attr.second;
                break;
            } else if (attr.first == "csk") {
                rowName = "Year: " + attr.second;
                break;
            }
        }
        if (rowName == "") {
            // Get text inside <a> tag, which is inside the table header (<th>) tag.
            html::Element date(html::getElementsByTag(row, "th").get(0));
            html::Collection hyperlinks(html::getElementsByTag(date, "a"));
            if (hyperlinks.length() == 0) {
                std::cerr << "ERROR: Failed to find name of row for table \""
                          << caption << std::endl;
                return 1;
            }
            rowName = "Time: " + hyperlinks.get(0).getText();
        }
        output.add(rowName, dataRow);
    }

    return 0;
}

/**
 * Scrapes the html output of the player page and stores only important
 * player data into output.
 * @param output The destination of where to store the scraped data
 * @param htmlResponse The HTML page of the player
 * @returns 0 if successful, 1 otherwise
*/
int Scraper::scrapeData(DataTableMap<std::string>& output,
                        const std::string& htmlResponse) {
    const html::Document document(html::parse(htmlResponse));

    const html::Collection tables(html::getElementsByTag(document, "table"));
    if (tables.length() == 0) {
        std::cerr << "ERROR: Failed to scrape tables for document\n"
                  << html::serialize_document(document) << std::endl;
        return 1;
    }
    for (size_t i = 0; i < tables.length(); i++) {
        const html::Element table(tables.get(i));
        std::string id(table.getId());
        if (id != "") {
            using Table = DataTable<std::string>;
            Table dataTable;
            int rc(scrapeTable(dataTable, table));
            if (rc) {
                return rc;
            }
            output.map().insert(std::pair<std::string, Table>(id, dataTable));
        } else {
            return 1;
        }
    }
    return 0;
}

Scraper::Scraper() noexcept(false) {

    // Initialize player ID map if not done.
    if (s_playerIdMap.empty()) {
        int rc(getPlayerList(s_playerIdMap));
        if (rc) {
            throw std::runtime_error("Cannot initialize player list.");
        }
    }
}

std::shared_ptr<DataTableMap<std::string>> Scraper::getPlayerData(
    const std::string& playerName) {
    using TableMap = DataTableMap<std::string>;
    std::string playerId;
    std::shared_ptr<TableMap> scrapedData(
        std::make_shared<TableMap>(DataTableMap<std::string>()));
    const DataTableMap<std::string> emptyMap;
    int rc(getPlayerId(playerId, playerName));
    if (rc) {
        return std::make_shared<DataTableMap<std::string>>(emptyMap);
    }
    std::string htmloutput;
    rc = getPlayerPage(htmloutput, playerId);
    if (rc) {
        return std::make_shared<DataTableMap<std::string>>(emptyMap);
    }
    rc = scrapeData(*scrapedData, htmloutput);
    if (rc) {
        return std::make_shared<DataTableMap<std::string>>(emptyMap);
    }
    return scrapedData;
}

}  // namespace pfrscraper