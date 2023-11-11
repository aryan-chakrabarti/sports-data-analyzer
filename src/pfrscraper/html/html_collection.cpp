#include "html_collection.h"
#include <stdexcept>

namespace pfrscraper {

namespace html {

Collection::Collection(lxb_dom_document_t* dom_document)
    : m_collection(lxb_dom_collection_make(dom_document, 128)),
      m_dom_document(dom_document) {
    if (m_collection == nullptr) {
        throw std::runtime_error("Failed to create collection object");
    }
}

Collection::Collection(const Collection& other)
    : Collection(other.m_dom_document) {
    *m_collection = *other.m_collection;
}

Collection::~Collection() {
    lxb_dom_collection_destroy(m_collection, true);
}

Collection& Collection::operator=(Collection other) {
    std::swap(*m_collection, *other.m_collection);
    std::swap(*m_dom_document, *other.m_dom_document);
    return *this;
}

lxb_dom_collection_t* Collection::c_collection() const {
    return m_collection;
}

lxb_dom_collection_t*& Collection::c_collection() {
    return m_collection;
}

Element Collection::get(size_t index) const {
    if (index >= length()) {
        throw std::out_of_range(
            "Index " + std::to_string(index) +
            " out of range while accessing collection of length " +
            std::to_string(length()));
    }
    Element elem(lxb_dom_collection_element(m_collection, index));
    return elem;
}

size_t Collection::length() const {
    return lxb_dom_collection_length(m_collection);
}

}  // namespace html

}  // namespace pfrscraper