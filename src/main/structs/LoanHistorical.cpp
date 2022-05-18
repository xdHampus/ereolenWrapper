#include "LoanHistorical.h"
#ifdef __cplusplus 
#include <functional>
#include <cstring>
#include <cstdlib>
//#include <cstdio>

    extern "C" { 
        namespace ereol {
#endif
            LoanHistorical*  ereol_LoanHistorical_instantiate()
            {
                return new LoanHistorical();
            }
            void ereol_LoanHistorical_delete(LoanHistorical* m)      
            { 
                delete m; 
            } 
            LoanIdentifier*  ereol_LoanHistorical_getLoanIdentifier(LoanHistorical* m) 
            { return &m->loanIdentifier; }
            void   ereol_LoanHistorical_setLoanIdentifier(LoanHistorical* m,  LoanIdentifier* identifier) 
            { m->loanIdentifier = *identifier; } 
            const char*  ereol_LoanHistorical_getLoanId(LoanHistorical* m) 
            { return m->loanId.c_str(); } 
            void   ereol_LoanHistorical_setLoanId(LoanHistorical* m,  const char* cp) 
            { m->loanId.assign(cp); }    
            int  ereol_LoanHistorical_getLoanDate(LoanHistorical* m) 
            { return m->loanDate; } 
            void   ereol_LoanHistorical_setLoanDate(LoanHistorical* m,  int utc)
            { m->loanDate = utc; }             
            bool  ereol_LoanHistorical_getManuallyAdded(LoanHistorical* m) 
            { return m->manuallyAdded; } 
            void   ereol_LoanHistorical_setManuallyAdded(LoanHistorical* m,  bool state) 
            { m->manuallyAdded = state; }   
            const char*  ereol_LoanHistorical_getTitle(LoanHistorical* m) 
            { return m->title.c_str(); } 
            void   ereol_LoanHistorical_setTitle(LoanHistorical* m,  const char* cp) 
            { m->title.assign(cp); }   
            const char*  ereol_LoanHistorical_getCreator(LoanHistorical* m) 
            { return m->creator.c_str(); } 
            void   ereol_LoanHistorical_setCreator(LoanHistorical* m, const char* cp) 
            { m->creator.assign(cp); }                 
            const char*  ereol_LoanHistorical_getPublicationDate(LoanHistorical* m) 
            { return m->publicationDate.c_str(); } 
            void   ereol_LoanHistorical_setPublicationDate(LoanHistorical* m, const char* cp) 
            { m->publicationDate.assign(cp); }    
            VectorStrC* ereol_LoanHistorical_getMaterialTypes(LoanHistorical* m) 
            { 
                return new VectorStrC(&m->materialTypes);
            } 
            size_t ereol_LoanHistorical_getMaterialTypes_size(LoanHistorical* m) 
            { return m->materialTypes.size();} 
            void ereol_LoanHistorical_getMaterialTypes_insert(LoanHistorical* m, const char* x) 
            { 
                std::string str(x);
                m->materialTypes.push_back(str); 
            } 
            void   ereol_LoanHistorical_setMaterialTypes(LoanHistorical* m, const char** arr, size_t n) 
            {  
                m->materialTypes = std::vector<std::string>(arr, arr + n); 
            } 
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 