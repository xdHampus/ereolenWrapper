#ifndef EREOLENWRAPPER_LOANACTIVE_H
#define EREOLENWRAPPER_LOANACTIVE_H

#include "LoanIdentifier.h"
#include <string>
namespace ereol {
    struct LoanActive {
        ereol::LoanIdentifier loanIdentifier;
        std::string retailerOrderNumber;
        std::string internalOrderNumber;
        int64_t orderDate = 0;
        int64_t expireDate = 0;
        std::string downloadUrl;
        bool isSubscription = false;
    };
    void from_json(const std::string  &s, ereol::LoanActive& x);
    void to_json(std::string & s, const ereol::LoanActive & x);    

}


#endif //EREOLENWRAPPER_LOANACTIVE_H
