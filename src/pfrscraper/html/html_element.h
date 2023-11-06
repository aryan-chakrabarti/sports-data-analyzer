#ifndef INCLUDE_HTML_ELEMENT
#define INCLUDE_HTML_ELEMENT

#include <lexbor/html/html.h>
#include <string>
#include <unordered_map>

namespace pfrscraper {

namespace html {

class Element {
    lxb_dom_element_t* m_element;

   public:
    Element(lxb_dom_element_t* element);
    lxb_dom_element_t*& c_element();
    std::string getAttribute(const std::string& attrName);
    std::string getId();
    std::unordered_map<std::string, std::string> getAttributes();
};

}  // namespace html

}  // namespace pfrscraper

#endif