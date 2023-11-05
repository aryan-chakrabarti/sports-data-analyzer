#include "html_document.h"
#include <iostream>
#include <stdexcept>

namespace pfrscraper {

namespace html {

Document::Document() : m_document(lxb_html_document_create()) {
    /* Initialization */
    if (m_document == nullptr) {
        throw std::runtime_error("Failed to create HTML document.");
    }
}

Document::Document(const Document& other) : Document() {
    *m_document = *other.m_document;
}

Document& Document::operator=(Document other) {
    std::swap(*m_document, *other.m_document);
    return *this;
}

Document::~Document() {
    /* Destroy document */
    lxb_html_document_destroy(m_document);
}

lxb_html_document_t*& Document::c_document() {
    return m_document;
}

Collection Document::getElementsByTag(const std::string& tag) const {
    lxb_status_t status;
    Collection collection(&m_document->dom_document);

    const lxb_char_t* tag_str =
        reinterpret_cast<const lxb_char_t*>(tag.c_str());
    status = lxb_dom_elements_by_tag_name(
        lxb_dom_interface_element(m_document->body), collection.c_collection(),
        tag_str, tag.size());

    if (status != LXB_STATUS_OK) {
        std::cout << "ERROR: Failed to get elements by name" << std::endl;
    }

    return collection;
}

}  // namespace html

}  // namespace pfrscraper