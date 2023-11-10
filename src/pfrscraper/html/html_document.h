#ifndef INCLUDE_HTML_DOCUMENT
#define INCLUDE_HTML_DOCUMENT

#include <lexbor/html/html.h>
#include <string>
#include "html_collection.h"

namespace pfrscraper {

namespace html {

class Document {

    lxb_html_document_t* m_document;

   public:
    Document();
    Document(const Document& other);
    ~Document();
    lxb_html_document_t* c_document() const;
    lxb_html_document_t*& c_document();
    Document& operator=(Document other);
    Collection getElementsByTag(const std::string& tag) const;
};

}  // namespace html

}  // namespace pfrscraper

#endif