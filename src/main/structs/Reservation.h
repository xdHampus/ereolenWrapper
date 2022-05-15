//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_RESERVATION_H
#define EREOLENWRAPPER_RESERVATION_H

#include "LoanIdentifier.h"
#ifdef __cplusplus 
#include <vector>
#include <string>
namespace ereol {
    struct Reservation {
        ereol::LoanIdentifier loanIdentifier;
        std::string bookId;
        std::string status;
        int createdUtc;
        int expireUtc;
        int expectedRedeemDateUtc;
    };
#else
//struct
typedef struct Reservation Reservation;
Reservation*     ereol_Reservation_instantiate(); 
void             ereol_Reservation_delete(Reservation* m);   
//loanIdentifier
LoanIdentifier*  ereol_Reservation_getLoanIdentifier(Reservation* m); 
void             ereol_Reservation_setLoanIdentifier(Reservation* m,  LoanIdentifier* identifier); 
//bookId
const char*      ereol_Reservation_getBookId(Reservation* m); 
void             ereol_Reservation_setBookId(Reservation* m,  char* cp); 
//status
const char*      ereol_Reservation_getStatus(Reservation* m); 
void             ereol_Reservation_setStatus(Reservation* m,  char* cp); 
//createdUtc
int              ereol_Reservation_getCreatedUTC(Reservation* m); 
void             ereol_Reservation_setCreatedUTC(Reservation* m,  int utc); 
//expireUtc
int              ereol_Reservation_getExpireUTC(Reservation* m); 
void             ereol_Reservation_setExpireUTC(Reservation* m,  int utc);
//expectedRedeemDateUtc 
int              ereol_Reservation_getExpectedRedeemDateUTC(Reservation* m); 
void             ereol_Reservation_setExpectedRedeemDateUTC(Reservation* m,  int utc);  
#endif
#ifdef __cplusplus 
}
#endif


#endif //EREOLENWRAPPER_RESERVATION_H
