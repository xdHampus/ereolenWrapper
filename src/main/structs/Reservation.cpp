#include "Reservation.h"
#ifdef __cplusplus 
    extern "C" { 
        namespace ereol {
#endif
            Reservation* ereol_Reservation_instantiate() 
            {
                return new Reservation();
            }
            void ereol_Reservation_delete(Reservation* m)   
            { 
               delete m;
            } 
            LoanIdentifier*  ereol_Reservation_getLoanIdentifier(Reservation* m) 
            { return &m->loanIdentifier; }
            void   ereol_Reservation_setLoanIdentifier(Reservation* m,  LoanIdentifier* identifier) 
            { m->loanIdentifier = *identifier; } 
            const char* ereol_Reservation_getBookId(Reservation* m) 
            { return m->bookId.c_str(); } 
            void ereol_Reservation_setBookId(Reservation* m,  char* cp) 
            { m->bookId.assign(cp); } 
            const char* ereol_Reservation_getStatus(Reservation* m) 
            { return m->status.c_str(); } 
            void ereol_Reservation_setStatus(Reservation* m,  char* cp) 
            { m->status.assign(cp); }             
            int ereol_Reservation_getCreatedUTC(Reservation* m) 
            { return m->createdUtc; } 
            void ereol_Reservation_setCreatedUTC(Reservation* m,  int utc) 
            { m->createdUtc = utc; } 
            int ereol_Reservation_getExpireUTC(Reservation* m) 
            { return m->expireUtc; } 
            void ereol_Reservation_setExpireUTC(Reservation* m,  int utc)
            { m->expireUtc = utc; } 
            int ereol_Reservation_getExpectedRedeemDateUTC(Reservation* m) 
            { return m->expectedRedeemDateUtc; } 
            void ereol_Reservation_setExpectedRedeemDateUTC(Reservation* m,  int utc)  
            { m->expectedRedeemDateUtc = utc; }             
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 