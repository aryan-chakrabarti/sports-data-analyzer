#include "html_serialize.h"
#include <lexbor/html/html.h>
#include <iostream>

namespace pfrscraper {

namespace html {

lxb_status_t serializer_callback(const lxb_char_t* data, size_t len,
                                 void* ctx) {
    (void)ctx;
    printf("%.*s", (int)len, (const char*)data);

    return LXB_STATUS_OK;
}

void serialize_document(Document& document) {
    lxb_status_t status;

    status = lxb_html_serialize_pretty_tree_cb(
        lxb_dom_interface_node(document.c_document()),
        LXB_HTML_SERIALIZE_OPT_UNDEF, 0, serializer_callback, NULL);
    if (status != LXB_STATUS_OK) {
        std::cout << "ERROR: Failed to serialize HTML tree" << std::endl;
    }
    return;
}

void serialize_node(lxb_dom_node_t* node) {
    lxb_status_t status;

    status = lxb_html_serialize_pretty_cb(node, LXB_HTML_SERIALIZE_OPT_UNDEF, 0,
                                          serializer_callback, NULL);
    if (status != LXB_STATUS_OK) {
        std::cout << "ERROR: Failed to serialize HTML node" << std::endl;
    }
}

void serialize_element(Element& element) {
    serialize_node(lxb_dom_interface_node(element.c_element()));
}

}  // namespace html

}  // namespace pfrscraper