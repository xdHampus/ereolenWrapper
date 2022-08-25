#ifndef EREOLENWRAPPER_RESERVATION_H
#define EREOLENWRAPPER_RESERVATION_H

#include "LoanIdentifier.h"
#include <string>
namespace ereol {
    struct Reservation {
        ereol::LoanIdentifier loanIdentifier;
        std::string bookId;
        std::string status;
        int64_t createdUtc;
        int64_t expireUtc;
        int64_t expectedRedeemDateUtc;
    };
    void from_json(const std::string  &s, ereol::Reservation& x);
    void to_json(std::string & s, const ereol::Reservation & x);       

}

#endif //EREOLENWRAPPER_RESERVATION_H
