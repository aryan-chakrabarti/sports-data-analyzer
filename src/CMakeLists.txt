add_library(pfrscrapercore pfrscraper_scraper.cpp pfrscraper_utils.cpp)
target_link_libraries(pfrscrapercore curlpp curl)
add_executable(pfrscraper.tsk pfrscraper.m.cpp)
target_link_libraries(pfrscraper.tsk pfrscrapercore)