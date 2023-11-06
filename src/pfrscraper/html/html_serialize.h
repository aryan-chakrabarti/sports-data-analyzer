#ifndef INCLUDE_HTML_SERIALIZE
#define INCLUDE_HTML_SERIALIZE

#include <string>
#include "html_document.h"
#include "html_element.h"

namespace pfrscraper {

namespace html {

std::string serialize_document(Document& document);
std::string serialize_element(Element& element, bool verbose = true);

}  // namespace html

}  // namespace pfrscraper

#endif