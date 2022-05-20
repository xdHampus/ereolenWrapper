#include "Reservation.h"
#ifdef __cplusplus 
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::Reservation& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Reservation & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::Reservation& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();
        x.bookId = j.at("bookid").get<std::string>();
        x.createdUtc = j.at("createdUtc").get<int64_t>();
        x.status = j.at("status").get<std::string>();
        x.expireUtc = j.at("expireUtc").get<int64_t>();
        x.expectedRedeemDateUtc = j.at("expectedRedeemDateUtc").get<int64_t>();     
    }

    void to_json(json & j, const ereol::Reservation & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;   
        j["bookid"] = x.bookId;
        j["createdUtc"] = x.createdUtc;
        j["status"] = x.status;
        j["expireUtc"] = x.expireUtc;
        j["expectedRedeemDateUtc"] = x.expectedRedeemDateUtc;        
    }
}
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
            int64_t ereol_Reservation_getCreatedUTC(Reservation* m) 
            { return m->createdUtc; } 
            void ereol_Reservation_setCreatedUTC(Reservation* m,  int64_t utc) 
            { m->createdUtc = utc; } 
            int64_t ereol_Reservation_getExpireUTC(Reservation* m) 
            { return m->expireUtc; } 
            void ereol_Reservation_setExpireUTC(Reservation* m,  int64_t utc)
            { m->expireUtc = utc; } 
            int64_t ereol_Reservation_getExpectedRedeemDateUTC(Reservation* m) 
            { return m->expectedRedeemDateUtc; } 
            void ereol_Reservation_setExpectedRedeemDateUTC(Reservation* m,  int64_t utc)  
            { m->expectedRedeemDateUtc = utc; }             
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 