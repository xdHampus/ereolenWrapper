#include "LoanActive.h"
#ifdef __cplusplus 
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::LoanActive& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::LoanActive & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::LoanActive& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();
        x.retailerOrderNumber = j.at("retailerOrderNumber").get<std::string>();
        x.internalOrderNumber = j.at("internalOrderNumber").get<std::string>();
        x.orderDate = j.at("orderDate").get<uint64_t>();
        x.expireDate = j.at("expireDate").get<uint64_t>();
        x.downloadUrl = j.at("downloadUrl").get<std::string>();
        x.isSubscription = j.at("isSubscription").get<bool>();
    }

    void to_json(json & j, const ereol::LoanActive & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;
        j["retailerOrderNumber"] = x.retailerOrderNumber;
        j["internalOrderNumber"] = x.internalOrderNumber;
        j["orderDate"] = x.orderDate;
        j["expireDate"] = x.expireDate;
        j["downloadUrl"] = x.downloadUrl;
        j["isSubscription"] = x.isSubscription;
    }
}
    extern "C" { 
        namespace ereol {
#endif
            LoanActive* ereol_LoanActive_instantiate()
            {
                return new LoanActive();
            }
            void ereol_LoanActive_delete(LoanActive* m)      
            { 
                delete m;
            } 
            LoanIdentifier* ereol_LoanActive_getLoanIdentifier(LoanActive* m) 
            { return &m->loanIdentifier; }
            void   ereol_LoanActive_setLoanIdentifier(LoanActive* m,  LoanIdentifier* identifier) 
            { m->loanIdentifier = *identifier; } 
            const char* ereol_LoanActive_getRetailerOrderNumber(LoanActive* m) 
            { return m->retailerOrderNumber.c_str(); } 
            void   ereol_LoanActive_setRetailerOrderNumber(LoanActive* m,  char* cp) 
            { m->retailerOrderNumber.assign(cp); } 
            const char* ereol_LoanActive_getInternalOrderNumber(LoanActive* m) 
            { return m->internalOrderNumber.c_str(); } 
            void ereol_LoanActive_setInternalOrderNumber(LoanActive* m,  char* cp) 
            { m->internalOrderNumber.assign(cp); }             
            uint64_t  ereol_LoanActive_getOrderDate(LoanActive* m) 
            { return m->orderDate; } 
            void ereol_LoanActive_setOrderDate(LoanActive* m,  uint64_t utc) 
            { m->orderDate = utc; } 
            uint64_t ereol_LoanActive_getExpireDate(LoanActive* m) 
            { return m->expireDate; } 
            void ereol_LoanActive_setExpireDate(LoanActive* m,  uint64_t utc) 
            { m->expireDate = utc; } 
            const char* ereol_LoanActive_getDownloadUrl(LoanActive* m) 
            { return m->downloadUrl.c_str(); } 
            void ereol_LoanActive_setDownloadUrl(LoanActive* m,  char* cp) 
            { m->downloadUrl.assign(cp); } 
            bool  ereol_LoanActive_getSubscription(LoanActive* m) 
            { return m->isSubscription; } 
            void ereol_LoanActive_setSubscription(LoanActive* m,  bool state) 
            { m->isSubscription = state; }    
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 