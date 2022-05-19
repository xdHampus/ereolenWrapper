#pragma once


#include <string>
#include <vector>
namespace ereol {

    struct LoanHistoryElement {
        std::string loanId;
        std::string identifier;
        uint64_t loanDate;
        bool manuallyAdded;
        std::string isbn;
        std::string title;
        std::string creator;
        std::string publicationDate;
        std::vector<std::string> materialTypes;
    };
}
