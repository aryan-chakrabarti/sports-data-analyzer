add_subdirectory(html)
add_library(pfrscrapercore 
    pfrscraper_scraper.cpp 
    pfrscraper_utils.cpp
    pfrscraper_data_table.h
)
target_link_libraries(pfrscrapercore curlpp curl html)