#include "LoanIdentifier.h"
#ifdef __cplusplus 
#include "../util/JSONHelper.h"
void ereol::from_json(const std::string  &s, ereol::LoanIdentifier& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::LoanIdentifier & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::LoanIdentifier& x) {
        x.identifier = j.at("identifier").get<std::string>();
        x.isbn = j.at("isbn").get<std::string>();
    }
    void to_json(json & j, const ereol::LoanIdentifier & x) {
        j = json::object();
        j["identifier"] = x.identifier;
        j["isbn"] = x.isbn;
    }
}
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
