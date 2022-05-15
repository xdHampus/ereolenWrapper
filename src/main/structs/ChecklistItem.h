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
        int creationDateUtc;
    };
#else
//struct
typedef struct ChecklistItem ChecklistItem;
ChecklistItem*  ereol_ChecklistItem_instantiate(); 
void ereol_ChecklistItem_delete(ChecklistItem* m);      
//loanIdentifier
LoanIdentifier*  ereol_ChecklistItem_getLoanIdentifier(ChecklistItem* m); 
void   ereol_ChecklistItem_setLoanIdentifier(ChecklistItem* m,  LoanIdentifier* identifier); 
//creationDateUtc
int  ereol_ChecklistItem_getCreationDateUTC(ChecklistItem* m); 
void   ereol_ChecklistItem_setCreationDateUTC(ChecklistItem* m,  int utc); 
#endif
#ifdef __cplusplus 
}
#endif
#endif //EREOLENWRAPPER_CHECKLISTITEM_H
