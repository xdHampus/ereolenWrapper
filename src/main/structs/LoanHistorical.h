//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_LOANHISTORICAL_H
#define EREOLENWRAPPER_LOANHISTORICAL_H

#include <vector>
#include <string>
#include "LoanIdentifier.h"

namespace ereol {
    struct LoanHistorical {
        ereol::LoanIdentifier loanIdentifier;
        std::string loanId;
        int loanDate;
        bool manuallyAdded;
        std::string title;
        std::string creator;
        std::string publicationDate;
        std::vector<std::string> materialTypes;
    };
}


#endif //EREOLENWRAPPER_LOANHISTORICAL_H
