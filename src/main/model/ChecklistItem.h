#ifndef EREOLENWRAPPER_CHECKLISTITEM_H
#define EREOLENWRAPPER_CHECKLISTITEM_H

#include "LoanIdentifier.h"

#include <vector>
#include <string>
namespace ereol {
    struct ChecklistItem {
        ereol::LoanIdentifier loanIdentifier;
        int64_t creationDateUtc = 0;
    };
    void from_json(const std::string  &s, ereol::ChecklistItem& x);
    void to_json(std::string & s, const ereol::ChecklistItem & x);
}
#endif //EREOLENWRAPPER_CHECKLISTITEM_H
