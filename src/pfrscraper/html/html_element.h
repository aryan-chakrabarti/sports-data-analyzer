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
    lxb_dom_element_t* c_element() const;
    std::string getAttribute(const std::string& attrName) const;
    std::string getId() const;
    std::unordered_map<std::string, std::string> getAttributes() const;
    std::string getText() const;
};

}  // namespace html

}  // namespace pfrscraper

#endif