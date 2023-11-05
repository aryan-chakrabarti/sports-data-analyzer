include_directories(pfrscraper)
add_subdirectory(pfrscraper)
add_executable(sports-data-analyzer.tsk sports-data-analyzer.m.cpp)
target_link_libraries(sports-data-analyzer.tsk pfrscrapercore)