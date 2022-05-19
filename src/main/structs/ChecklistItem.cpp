#include "ChecklistItem.h"
#ifdef __cplusplus 
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::ChecklistItem& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::ChecklistItem & x){
    nlohmann::json j = x;
    s = j.dump();
}

    extern "C" { 
        namespace ereol {
#endif
            ChecklistItem*  ereol_ChecklistItem_instantiate()
            {
                return new ChecklistItem();
            }
            void ereol_ChecklistItem_delete(ChecklistItem* m)  
            { 
                delete m; 
            } 
            LoanIdentifier*  ereol_ChecklistItem_getLoanIdentifier(ChecklistItem* m)
            { return &m->loanIdentifier; }
            void   ereol_ChecklistItem_setLoanIdentifier(ChecklistItem* m, LoanIdentifier* identifier)
            { m->loanIdentifier = *identifier; } 
            uint64_t  ereol_ChecklistItem_getCreationDateUTC(ChecklistItem* m)
            { return m->creationDateUtc; } 
            void   ereol_ChecklistItem_setCreationDateUTC(ChecklistItem* m,  int utc)
            { m->creationDateUtc = utc; } 

#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 