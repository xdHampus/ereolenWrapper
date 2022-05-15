#include "ChecklistItem.h"
#ifdef __cplusplus 
    extern "C" { 
        namespace ereol {
#endif
            ChecklistItem*  ereol_ChecklistItem_instantiate()
            {
                return new ChecklistItem();
            }
            void ereol_ChecklistItem_delete(ChecklistItem* m)  
            { 
                m->~ChecklistItem();  
            } 
            LoanIdentifier*  ereol_ChecklistItem_getLoanIdentifier(ChecklistItem* m)
            { return &m->loanIdentifier; }
            void   ereol_ChecklistItem_setLoanIdentifier(ChecklistItem* m, LoanIdentifier* identifier)
            { m->loanIdentifier = *identifier; } 
            int  ereol_ChecklistItem_getCreationDateUTC(ChecklistItem* m)
            { return m->creationDateUtc; } 
            void   ereol_ChecklistItem_setCreationDateUTC(ChecklistItem* m,  int utc)
            { m->creationDateUtc = utc; } 

#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 