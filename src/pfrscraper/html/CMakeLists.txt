add_library(html 
    html_parse.cpp
    html_document.cpp
    html_serialize.cpp
    html_collection.cpp
    html_element.cpp
    html_utils.h
)
target_link_libraries(html lexbor)