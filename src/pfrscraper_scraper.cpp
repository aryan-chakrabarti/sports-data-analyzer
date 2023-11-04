#include "pfrscraper_scraper.h"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace pfrscraper {

std::string generatePlayerUrl(const std::string& playerId) {
    std::ostringstream sstream;
    sstream << "https://www.pro-football-reference.com/players/"
            << playerId.at(0) << playerId << ".htm";
    return sstream.str();
}

/**
 * Makes a request to the given url, and puts the result in 'output'
 * @param output The destination of the curl response.
 * @param requestUrl The url to get the data from.
 * @returns 0 if successful, 1 otherwise. Will set output to an empty
 *  string on failure.
*/
int getResponseString(std::string* output, const std::string& requestUrl) {
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

        *output = response.str();

        return 0;
    }

    catch (curlpp::RuntimeError& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        *output = "";
        return 1;
    }

    catch (curlpp::LogicError& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        *output = "";
        return 1;
    }
}

void getPlayerList(std::string* output) {
    const std::string requestUrl(
        "https://www.pro-football-reference.com/short/inc/"
        "players_search_list.csv");
    int rc(getResponseString(output, requestUrl));
    if (rc) {
        std::cout << "ERROR: Failed to get player list" << std::endl;
    }
}

void getPlayerPage(std::string* output, const std::string& playerId) {
    const std::string url(generatePlayerUrl(playerId));
    int rc(getResponseString(output, url));
    if (rc) {
        std::cout << "ERROR: Failed to get player page for " << playerId
                  << std::endl;
    }
}

Scraper::Scraper(const std::string& playerName) : m_playerName(playerName) {}

Scraper::Scraper(const Scraper& scraper) : m_playerName(scraper.m_playerName) {}

Scraper::~Scraper() {}

std::string& Scraper::playerName() {
    return m_playerName;
}

const std::string& Scraper::playerName() const {
    return m_playerName;
}

/**
 * Retrieves player data and returns as a strign.
 * If data is invalid, output is an empty string.
 * @returns player data as a string, empty if invalid.
*/
std::string Scraper::getPlayerData() {
    std::string output;
    getPlayerList(&output);
    return output;
}

std::string scrapeData(const std::string& htmlResponse) {
    return htmlResponse;
}

}  // namespace pfrscraper