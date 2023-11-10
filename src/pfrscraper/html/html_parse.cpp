#include "html_parse.h"
#include <iostream>
#include "html_utils.h"

namespace pfrscraper {

namespace html {

Document parse(const std::string& htmlResponse) {
    lxb_status_t status;
    Document document;
    const lxb_char_t* htmlStr =
        reinterpret_cast<const lxb_char_t*>(htmlResponse.c_str());

    /* Parse HTML */
    status = lxb_html_document_parse(document.c_document(), htmlStr,
                                     htmlResponse.size());
    if (status != LXB_STATUS_OK) {
        std::cerr << "ERROR: Failed to parse HTML." << std::endl;
        return document;
    }

    return document;
}

Collection getElementsByTag(const Document& document, const std::string& tag) {
    lxb_status_t status;
    Collection collection(&document.c_document()->dom_document);

    const lxb_char_t* tag_str =
        reinterpret_cast<const lxb_char_t*>(tag.c_str());
    status = lxb_dom_elements_by_tag_name(
        lxb_dom_interface_element(document.c_document()->body),
        collection.c_collection(), tag_str, tag.size());

    if (status != LXB_STATUS_OK) {
        std::cerr << "ERROR: Failed to get elements by name" << std::endl;
    }

    return collection;
}

Collection getElementsByTag(const Element& element,
                            const std::string& tagName) {
    Collection collection(
        lxb_dom_interface_node(element.c_element())->owner_document);
    lxb_status_t status(lxb_dom_elements_by_tag_name(
        element.c_element(), collection.c_collection(),
        string_to_lxb_char(tagName), tagName.size()));
    if (status != LXB_STATUS_OK) {
        std::cerr << "ERROR: Failed to get elements by tag of " << tagName
                  << std::endl;
    }
    return collection;
}

}  // namespace html

}  // namespace pfrscraper