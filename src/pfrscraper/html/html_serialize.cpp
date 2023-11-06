#include "html_serialize.h"
#include <lexbor/html/html.h>
#include <iostream>
#include "html_utils.h"

namespace pfrscraper {

namespace html {

lxb_status_t serializer_callback(const lxb_char_t* data, size_t len,
                                 void* ctx) {
    ((std::string*)ctx)->append(lxb_char_to_string(data));
    return LXB_STATUS_OK;
}

std::string serialize_tree(lxb_dom_node_t* node) {
    lxb_status_t status;
    std::string serialized_tree;
    status = lxb_html_serialize_pretty_tree_cb(
        node, LXB_HTML_SERIALIZE_OPT_UNDEF, 0, serializer_callback,
        &serialized_tree);
    if (status != LXB_STATUS_OK) {
        std::cerr << "ERROR: Failed to serialize HTML tree" << std::endl;
        return "";
    }
    return serialized_tree;
}

std::string serialize_node(lxb_dom_node_t* node) {
    lxb_status_t status;
    std::string serialized_node;
    status =
        lxb_html_serialize_pretty_cb(node, LXB_HTML_SERIALIZE_OPT_UNDEF, 0,
                                     serializer_callback, &serialized_node);
    if (status != LXB_STATUS_OK) {
        std::cerr << "ERROR: Failed to serialize HTML node" << std::endl;
        return "";
    }
    return serialized_node;
}

std::string serialize_document(Document& document) {
    return serialize_tree(lxb_dom_interface_node(document.c_document()));
}

std::string serialize_element(Element& element, bool verbose) {
    if (verbose) {
        return serialize_tree(lxb_dom_interface_node(element.c_element()));
    } else {
        return serialize_node(lxb_dom_interface_node(element.c_element()));
    }
}

}  // namespace html

}  // namespace pfrscraper