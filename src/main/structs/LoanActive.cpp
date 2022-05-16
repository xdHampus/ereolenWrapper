#include "LoanActive.h"
#ifdef __cplusplus 
    extern "C" { 
        namespace ereol {
#endif
            LoanActive*  ereol_LoanActive_instantiate()
            {
                return new LoanActive();
            }
            void ereol_LoanActive_delete(LoanActive* m)      
            { 
                delete m;
            } 
            LoanIdentifier*  ereol_LoanActive_getLoanIdentifier(LoanActive* m) 
            { return &m->loanIdentifier; }
            void   ereol_LoanActive_setLoanIdentifier(LoanActive* m,  LoanIdentifier* identifier) 
            { m->loanIdentifier = *identifier; } 
            const char*  ereol_LoanActive_getRetailerOrderNumber(LoanActive* m) 
            { return m->retailerOrderNumber.c_str(); } 
            void   ereol_LoanActive_setRetailerOrderNumber(LoanActive* m,  char* cp) 
            { m->retailerOrderNumber.assign(cp); } 
            const char*  ereol_LoanActive_getInternalOrderNumber(LoanActive* m) 
            { return m->internalOrderNumber.c_str(); } 
            void   ereol_LoanActive_setInternalOrderNumber(LoanActive* m,  char* cp) 
            { m->internalOrderNumber.assign(cp); }             
            int  ereol_LoanActive_getOrderDate(LoanActive* m) 
            { return m->orderDate; } 
            void   ereol_LoanActive_setOrderDate(LoanActive* m,  int utc) 
            { m->orderDate = utc; } 
            int  ereol_LoanActive_getExpireDate(LoanActive* m) 
            { return m->expireDate; } 
            void   ereol_LoanActive_setExpireDate(LoanActive* m,  int utc) 
            { m->expireDate = utc; } 
            const char*  ereol_LoanActive_getDownloadUrl(LoanActive* m) 
            { return m->downloadUrl.c_str(); } 
            void   ereol_LoanActive_setDownloadUrl(LoanActive* m,  char* cp) 
            { m->downloadUrl.assign(cp); } 
            bool  ereol_LoanActive_getSubscription(LoanActive* m) 
            { return m->isSubscription; } 
            void   ereol_LoanActive_setSubscription(LoanActive* m,  bool state) 
            { m->isSubscription = state; }    
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 