add_library(html html_parse.cpp html_document.cpp html_serialize.h html_collection.cpp html_element.cpp)
target_link_libraries(html lexbor)