#ifndef INCLUDE_HTML_UTILS
#define INCLUDE_HTML_UTILS

#include <lexbor/html/html.h>
#include <string>

namespace pfrscraper {

namespace html {

inline std::string lxb_char_to_string(const lxb_char_t* str) {
    return std::string(reinterpret_cast<const char*>(str));
}

inline const lxb_char_t* string_to_lxb_char(const std::string& str) {
    return reinterpret_cast<const lxb_char_t*>(str.c_str());
}

}  // namespace html

}  // namespace pfrscraper

#endif