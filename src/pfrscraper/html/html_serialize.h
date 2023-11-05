#ifndef INCLUDE_HTML_SERIALIZE
#define INCLUDE_HTML_SERIALIZE

#include "html_document.h"
#include "html_element.h"

namespace pfrscraper {

namespace html {

void serialize_document(Document& document);
void serialize_element(Element& element);

}  // namespace html

}  // namespace pfrscraper

#endif