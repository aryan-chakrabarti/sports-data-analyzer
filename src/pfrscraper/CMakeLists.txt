add_subdirectory(html)
include_directories(html)
add_library(pfrscrapercore pfrscraper_scraper.cpp pfrscraper_utils.cpp)
target_link_libraries(pfrscrapercore curlpp curl html)