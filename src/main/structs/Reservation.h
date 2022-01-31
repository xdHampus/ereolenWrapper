//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_RESERVATION_H
#define EREOLENWRAPPER_RESERVATION_H

#include <vector>
#include <string>
#include "LoanIdentifier.h"

namespace ereol {
    struct Reservation {
        ereol::LoanIdentifier loanIdentifier;
        std::string bookId;
        std::string status;
        int createdUtc;
        int expireUtc;
        int expectedRedeemDateUtc;
    };
}


#endif //EREOLENWRAPPER_RESERVATION_H
