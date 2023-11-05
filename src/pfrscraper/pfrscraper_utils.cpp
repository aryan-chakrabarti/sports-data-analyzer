#include "pfrscraper_utils.h"
#include <cstring>

namespace pfrscraper {

std::string to_upper(std::string str) {
    for (auto& c : str) {
        c = (char)std::toupper(c);
    }
    return str;
}

}  // namespace pfrscraper