#ifndef INCLUDE_HTML_PARSER
#define INCLUDE_HTML_PARSER

#include <lexbor/html/html.h>
#include <string>
#include "html_document.h"

namespace pfrscraper {

namespace html {

/**
 * Parses the HTML response received into an HTML
 * parse tree.
 * @param htmlResponse The string value of the HTML document.
 * @returns The corresponding HTML document structure containing the tree.
*/
Document parse(const std::string& htmlResponse);

}  // namespace html

}  // namespace pfrscraper

#endif