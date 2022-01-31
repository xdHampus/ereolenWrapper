//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_LOANACTIVE_H
#define EREOLENWRAPPER_LOANACTIVE_H

#include <vector>
#include <string>
#include "LoanIdentifier.h"

namespace ereol {
    struct LoanActive {
        ereol::LoanIdentifier loanIdentifier;
        std::string retailerOrderNumber;
        std::string internalOrderNumber;
        int orderDate;
        int expireDate;
        std::string downloadUrl;
        bool isSubscription;
    };
}



#endif //EREOLENWRAPPER_LOANACTIVE_H
