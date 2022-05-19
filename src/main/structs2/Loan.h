#pragma once

#include <string>
namespace ereol {
    struct Loan {
        std::string identifier;
        std::string isbn;
        std::string retailerOrderNumber;
        std::string internalOrderNumber;
        uint64_t orderDate;
        uint64_t expireDate;
        std::string downloadUrl;
        bool isSubscription;
    };
}
