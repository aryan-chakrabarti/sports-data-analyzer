#ifndef INCLUDE_HTML_PARSER
#define INCLUDE_HTML_PARSER

#include <lexbor/html/html.h>
#include <string>
#include "html_collection.h"
#include "html_document.h"
#include "html_element.h"

namespace pfrscraper {

namespace html {

/**
 * Parses the HTML response received into an HTML
 * parse tree.
 * @param htmlResponse The string value of the HTML document.
 * @returns The corresponding HTML document structure containing the tree.
*/
Document parse(const std::string& htmlResponse);

Collection getElementsByTag(const Document& document,
                            const std::string& tagName);
Collection getElementsByTag(const Element& element, const std::string& tagName);

Collection getElementsByClass(const Element& element,
                              const std::string& className);

}  // namespace html

}  // namespace pfrscraper

#endif