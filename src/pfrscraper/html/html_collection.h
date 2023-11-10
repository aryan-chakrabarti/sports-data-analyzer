#ifndef INCLUDE_HTML_COLLECTION
#define INCLUDE_HTML_COLLECTION

#include <lexbor/html/html.h>
#include "html_element.h"

namespace pfrscraper {

namespace html {

class Collection {

    lxb_dom_collection_t* m_collection;
    lxb_dom_document_t* m_dom_document;

   public:
    Collection(lxb_dom_document_t* dom_document);
    Collection(const Collection& other);
    ~Collection();
    Collection& operator=(Collection other);
    lxb_dom_collection_t* c_collection() const;
    lxb_dom_collection_t*& c_collection();
    Element get(size_t index) const;
    size_t length() const;
};

}  // namespace html

}  // namespace pfrscraper

#endif