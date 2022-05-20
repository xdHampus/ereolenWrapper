//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_RESERVATION_H
#define EREOLENWRAPPER_RESERVATION_H

#include "LoanIdentifier.h"
#ifdef __cplusplus 
#include <string>
namespace ereol {
    struct Reservation {
        ereol::LoanIdentifier loanIdentifier;
        std::string bookId;
        std::string status;
        int64_t createdUtc;
        int64_t expireUtc;
        int64_t expectedRedeemDateUtc;
    };
    void from_json(const std::string  &s, ereol::Reservation& x);
    void to_json(std::string & s, const ereol::Reservation & x);       
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
int64_t              ereol_Reservation_getCreatedUTC(Reservation* m); 
void             ereol_Reservation_setCreatedUTC(Reservation* m,  int64_t utc); 
//expireUtc
int64_t              ereol_Reservation_getExpireUTC(Reservation* m); 
void             ereol_Reservation_setExpireUTC(Reservation* m,  int64_t utc);
//expectedRedeemDateUtc 
int64_t              ereol_Reservation_getExpectedRedeemDateUTC(Reservation* m); 
void             ereol_Reservation_setExpectedRedeemDateUTC(Reservation* m,  int64_t utc);  
#endif
#ifdef __cplusplus 
}
#endif


#endif //EREOLENWRAPPER_RESERVATION_H
