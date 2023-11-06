#include "html_element.h"
#include <iostream>
#include "html_utils.h"

namespace pfrscraper {

namespace html {

Element::Element(lxb_dom_element_t* element) : m_element(element) {}

lxb_dom_element_t*& Element::c_element() {
    return m_element;
}

std::string Element::getAttribute(const std::string& attrName) {
    if (attrName == "id") {
        return getId();
    }
    /* Get value by qualified name */
    size_t value_len;
    const lxb_char_t* value = lxb_dom_element_get_attribute(
        m_element, string_to_lxb_char(attrName), attrName.size(), &value_len);
    if (value == NULL) {
        std::cerr << "ERROR: Failed to get attribute value by name " << attrName
                  << std::endl;
        return "";
    }
    return lxb_char_to_string(value);
}

std::string Element::getId() {
    size_t value_len;
    const lxb_char_t* value(lxb_dom_element_id(m_element, &value_len));
    if (value == NULL) {
        std::cerr << "ERROR: Failed to get ID for element" << std::endl;
        return "";
    }
    return lxb_char_to_string(value);
}

std::unordered_map<std::string, std::string> Element::getAttributes() {
    /* Iterator */
    lxb_dom_attr_t* attr(lxb_dom_element_first_attribute(m_element));
    std::unordered_map<std::string, std::string> attribute_map;
    while (attr != NULL) {
        size_t tmp_len;
        const lxb_char_t* name(lxb_dom_attr_qualified_name(attr, &tmp_len));

        const lxb_char_t* value(lxb_dom_attr_value(attr, &tmp_len));
        if (value == NULL) {
            std::cerr << "ERROR: No value found for attribute name " << name
                      << std::endl;
        } else {
            attribute_map.insert(std::pair<std::string, std::string>(
                lxb_char_to_string(name), lxb_char_to_string(value)));
        }

        attr = lxb_dom_element_next_attribute(attr);
    }
    return attribute_map;
}

}  // namespace html

}  // namespace pfrscraper