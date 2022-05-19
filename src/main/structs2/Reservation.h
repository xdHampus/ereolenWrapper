#pragma once

#include <string>
namespace ereol {
    struct Reservation {
        std::string identifier;
        std::string isbn;
        std::string bookid;
        uint64_t createdUtc;
        std::string status;
        uint64_t expireUtc;
        uint64_t expectedRedeemDateUtc;
    };
}
