#include "pfrscraper_utils.h"
#include <cstring>
#include <iostream>
namespace pfrscraper {

std::string to_proper(std::string str) {
    bool wasSpace(true);
    for (auto& c : str) {
        bool isSeparator(c == ' ' || c == '\n' || c == '\t');
        if (wasSpace && !isSeparator) {
            c = (char)std::toupper(c);
            wasSpace = false;
        } else if (isSeparator) {
            wasSpace = true;
        }
    }
    return str;
}

}  // namespace pfrscraper