#ifndef EREOLENWRAPPER_LOANHISTORICAL_H
#define EREOLENWRAPPER_LOANHISTORICAL_H
#include "LoanIdentifier.h"
#include <vector>
#include <string>
namespace ereol {
    struct LoanHistorical {
        ereol::LoanIdentifier loanIdentifier;
        std::string loanId;
        int64_t loanDate = 0;
        bool manuallyAdded = false;
        std::string title;
        std::string creator;
        std::string publicationDate;
        std::vector<std::string> materialTypes;
    };

    void from_json(const std::string  &s, ereol::LoanHistorical& x);
    void to_json(std::string & s, const ereol::LoanHistorical & x);        
}
#endif //EREOLENWRAPPER_LOANHISTORICAL_H
