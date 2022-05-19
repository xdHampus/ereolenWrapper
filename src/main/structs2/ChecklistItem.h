#pragma once

#include <string>
namespace ereol {
    struct ChecklistItem {
        std::string identifier;
        std::string isbn;
        uint64_t creationDateUtc;
    };
}