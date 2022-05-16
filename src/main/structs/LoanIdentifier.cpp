#include "LoanIdentifier.h"

#ifdef __cplusplus 
    extern "C" { 
        namespace ereol {
#endif
            LoanIdentifier*  ereol_LoanIdentifier_instantiate()
            {
                return new LoanIdentifier();
            }
            void ereol_LoanIdentifier_delete(LoanIdentifier* m)  
            { 
                delete m;
            } 
            const char*  ereol_LoanIdentifier_getIdentifier(LoanIdentifier* m)  
            { return m->identifier.c_str(); }
            void   ereol_LoanIdentifier_setIdentifier(LoanIdentifier* m,  char* cp)  
            { m->identifier.assign(cp); } 
            const char*  ereol_LoanIdentifier_getISBN(LoanIdentifier* m)  
            { return m->isbn.c_str(); } 
            void   ereol_LoanIdentifier_setISBN(LoanIdentifier* m,  char* cp)  
            { m->isbn.assign(cp); } 
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 
