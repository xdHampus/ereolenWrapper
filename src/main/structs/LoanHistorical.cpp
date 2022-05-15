#include "LoanHistorical.h"
#ifdef __cplusplus 
#include <functional>
    extern "C" { 
        namespace ereol {
#endif
            LoanHistorical*  ereol_LoanHistorical_instantiate()
            {
                return new LoanHistorical();
            }
            void ereol_LoanHistorical_delete(LoanHistorical* m)      
            { 
                m->~LoanHistorical();  
            } 
            LoanIdentifier*  ereol_LoanHistorical_getLoanIdentifier(LoanHistorical* m) 
            { return &m->loanIdentifier; }
            void   ereol_LoanHistorical_setLoanIdentifier(LoanHistorical* m,  LoanIdentifier* identifier) 
            { m->loanIdentifier = *identifier; } 
            const char*  ereol_LoanHistorical_getLoanId(LoanHistorical* m) 
            { return m->loanId.c_str(); } 
            void   ereol_LoanHistorical_setLoanId(LoanHistorical* m,  char* cp) 
            { m->loanId.assign(cp); }    
            int  ereol_LoanHistorical_geLoanDate(LoanHistorical* m) 
            { return m->loanDate; } 
            void   ereol_LoanHistorical_setLoanDate(LoanHistorical* m,  int utc)
            { m->loanDate = utc; }             
            bool  ereol_LoanHistorical_getManuallyAdded(LoanHistorical* m) 
            { return m->manuallyAdded; } 
            void   ereol_LoanHistorical_setManuallyAdded(LoanHistorical* m,  bool state) 
            { m->manuallyAdded = state; }   
            const char*  ereol_LoanHistorical_getTitle(LoanHistorical* m) 
            { return m->title.c_str(); } 
            void   ereol_LoanHistorical_setTitle(LoanHistorical* m,  char* cp) 
            { m->title.assign(cp); }   
            const char*  ereol_LoanHistorical_getCreator(LoanHistorical* m) 
            { return m->creator.c_str(); } 
            void   ereol_LoanHistorical_setCreator(LoanHistorical* m,  char* cp) 
            { m->creator.assign(cp); }                 
            const char*  ereol_LoanHistorical_getPublicationDate(LoanHistorical* m) 
            { return m->publicationDate.c_str(); } 
            void   ereol_LoanHistorical_setPublicationDate(LoanHistorical* m,  char* cp) 
            { m->publicationDate.assign(cp); }    
            const char**  ereol_LoanHistorical_getMaterialTypes(LoanHistorical* m) 
            { 
                std::vector<const char*> c_strs;
                std::transform(std::begin(m->materialTypes), std::end(m->materialTypes), std::back_inserter(c_strs), std::mem_fn(&std::string::c_str));
                return c_strs.data(); 
            } 
            size_t ereol_LoanHistorical_getMaterialTypes_size(LoanHistorical* m) 
            { return m->materialTypes.size();} 
            void ereol_LoanHistorical_getMaterialTypes_insert(LoanHistorical* m, char* x) 
            { 
                std::string str(x);
                m->materialTypes.push_back(str); 
            } 
            void   ereol_LoanHistorical_setMaterialTypes(LoanHistorical* m,  char** arr, size_t n) 
            {  
                m->materialTypes = std::vector<std::string>(arr, arr + n); 
            } 
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 