//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_TOKEN_H
#define EREOLENWRAPPER_TOKEN_H

#include <string>
#include "Library.h"

namespace ereol {
    struct Token {
        int timeFetched;
        std::string sessid;
        std::string expirationDate;
        ereol::Library library;
    };
}

#endif //EREOLENWRAPPER_TOKEN_H
