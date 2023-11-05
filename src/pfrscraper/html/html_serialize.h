#ifndef INCLUDE_HTML_SERIALIZE
#define INCLUDE_HTML_SERIALIZE

#include <lexbor/html/html.h>
#include <iostream>

namespace pfrscraper {

namespace html {

lxb_inline lxb_status_t serializer_callback(const lxb_char_t* data, size_t len,
                                            void* ctx) {
    (void)ctx;
    printf("%.*s", (int)len, (const char*)data);

    return LXB_STATUS_OK;
}

lxb_inline void serialize_document(lxb_html_document_t*& document) {
    lxb_status_t status;

    status = lxb_html_serialize_pretty_tree_cb(lxb_dom_interface_node(document),
                                               LXB_HTML_SERIALIZE_OPT_UNDEF, 0,
                                               serializer_callback, NULL);
    if (status != LXB_STATUS_OK) {
        std::cout << "ERROR: Failed to serialize HTML tree" << std::endl;
    }
    return;
}

lxb_inline void serialize_node(lxb_dom_node_t* node) {
    lxb_status_t status;

    status = lxb_html_serialize_pretty_cb(node, LXB_HTML_SERIALIZE_OPT_UNDEF, 0,
                                          serializer_callback, NULL);
    if (status != LXB_STATUS_OK) {
        std::cout << "ERROR: Failed to serialize HTML node" << std::endl;
    }
}

lxb_inline void serialize_element(lxb_dom_element_t* element) {
    serialize_node(lxb_dom_interface_node(element));
}

}  // namespace html

}  // namespace pfrscraper

#endif