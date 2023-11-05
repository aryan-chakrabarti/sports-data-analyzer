#include "html_element.h"

namespace pfrscraper {

namespace html {

Element::Element(lxb_dom_element_t* element) : m_element(element) {}

lxb_dom_element_t*& Element::c_element() {
    return m_element;
}

}  // namespace html

}  // namespace pfrscraper