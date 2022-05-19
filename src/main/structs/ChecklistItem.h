//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_CHECKLISTITEM_H
#define EREOLENWRAPPER_CHECKLISTITEM_H
#include "LoanIdentifier.h"
#ifdef __cplusplus 
#include <vector>
#include <string>
namespace ereol {
    struct ChecklistItem {
        ereol::LoanIdentifier loanIdentifier;
        uint64_t creationDateUtc;
    };
    void from_json(const std::string  &s, ereol::ChecklistItem& x);
    void to_json(std::string & s, const ereol::ChecklistItem & x);
#else
//struct
typedef struct ChecklistItem ChecklistItem;
ChecklistItem*  ereol_ChecklistItem_instantiate(); 
void ereol_ChecklistItem_delete(ChecklistItem* m);      
//loanIdentifier
LoanIdentifier*  ereol_ChecklistItem_getLoanIdentifier(ChecklistItem* m); 
void   ereol_ChecklistItem_setLoanIdentifier(ChecklistItem* m,  LoanIdentifier* identifier); 
//creationDateUtc
uint64_t  ereol_ChecklistItem_getCreationDateUTC(ChecklistItem* m); 
void   ereol_ChecklistItem_setCreationDateUTC(ChecklistItem* m,  int utc); 
#endif
#ifdef __cplusplus 
}
#endif
#endif //EREOLENWRAPPER_CHECKLISTITEM_H
