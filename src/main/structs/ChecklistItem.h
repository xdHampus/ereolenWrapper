//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_CHECKLISTITEM_H
#define EREOLENWRAPPER_CHECKLISTITEM_H

#include <vector>
#include <string>
#include "LoanIdentifier.h"

namespace ereol {
    struct ChecklistItem {
        ereol::LoanIdentifier loanIdentifier;
        int creationDateUtc;
    };
}


#endif //EREOLENWRAPPER_CHECKLISTITEM_H
