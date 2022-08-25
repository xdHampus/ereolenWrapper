#ifndef EREOLENWRAPPER_TOKEN_H
#define EREOLENWRAPPER_TOKEN_H

#include "Library.h"
#include <string>
namespace ereol {
    struct Token {
        int64_t timeFetched;
        std::string sessid;
        std::string expirationDate;
        ereol::Library library;
    };
}
#endif //EREOLENWRAPPER_TOKEN_H
