#ifndef EREOLENWRAPPER_LOANACTIVE_H
#define EREOLENWRAPPER_LOANACTIVE_H

#include "LoanIdentifier.h"
#ifdef __cplusplus 
#include <string>
namespace ereol {
    struct LoanActive {
        ereol::LoanIdentifier loanIdentifier;
        std::string retailerOrderNumber;
        std::string internalOrderNumber;
        int64_t orderDate;
        int64_t expireDate;
        std::string downloadUrl;
        bool isSubscription;
    };
    void from_json(const std::string  &s, ereol::LoanActive& x);
    void to_json(std::string & s, const ereol::LoanActive & x);    
#else
#include <stdbool.h>
//struct
typedef struct LoanActive LoanActive;
LoanActive*  ereol_LoanActive_instantiate(); 
void ereol_LoanActive_delete(LoanActive* m); 
//loanIdentifier
LoanIdentifier*  ereol_LoanActive_getLoanIdentifier(LoanActive* m); 
void   ereol_LoanActive_setLoanIdentifier(LoanActive* m,  LoanIdentifier* identifier); 
//retailerOrderNumber
const char*  ereol_LoanActive_getRetailerOrderNumber(LoanActive* m); 
void   ereol_LoanActive_setRetailerOrderNumber(LoanActive* m,  char* cp); 
//internalOrderNumber
const char*  ereol_LoanActive_getInternalOrderNumber(LoanActive* m); 
void   ereol_LoanActive_setInternalOrderNumber(LoanActive* m,  char* cp); 
//orderDate
int64_t  ereol_LoanActive_getOrderDate(LoanActive* m); 
void   ereol_LoanActive_setOrderDate(LoanActive* m,  int64_t utc); 
//expireDate
int64_t  ereol_LoanActive_getExpireDate(LoanActive* m); 
void   ereol_LoanActive_setExpireDate(LoanActive* m,  int64_t utc); 
//downloadUrl
const char*  ereol_LoanActive_getDownloadUrl(LoanActive* m); 
void   ereol_LoanActive_setDownloadUrl(LoanActive* m,  char* cp); 
//isSubscription
bool  ereol_LoanActive_getSubscription(LoanActive* m); 
void   ereol_LoanActive_setSubscription(LoanActive* m,  bool state); 
#endif
#ifdef __cplusplus 
}
#endif


#endif //EREOLENWRAPPER_LOANACTIVE_H
