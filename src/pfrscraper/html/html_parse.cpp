#include "html_parse.h"
#include <iostream>

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
        std::cout << "ERROR: Failed to parse HTML." << std::endl;
        return document;
    }

    return document;
}

}  // namespace html

}  // namespace pfrscraper