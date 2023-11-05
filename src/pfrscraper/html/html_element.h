#ifndef INCLUDE_HTML_ELEMENT
#define INCLUDE_HTML_ELEMENT

#include <lexbor/html/html.h>

namespace pfrscraper {

namespace html {

class Element {
    lxb_dom_element_t* m_element;

   public:
    Element(lxb_dom_element_t* element);
    lxb_dom_element_t*& c_element();
};

}  // namespace html

}  // namespace pfrscraper

#endif