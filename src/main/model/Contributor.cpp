#include "Contributor.h"
#ifdef __cplusplus 
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::Contributor& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Contributor & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::Contributor& x) {
        x.type = j.at("type").get<std::string>();
        x.composedName = j.at("composedName").get<std::string>();
        x.firstName = j.at("firstName").get<std::string>();
        x.lastName = j.at("lastName").get<std::string>();
    }
    void to_json(json & j, const ereol::Contributor & x) {
        j = json::object();
        j["type"] = x.type;
        j["composedName"] = x.composedName;
        j["firstName"] = x.firstName;
        j["lastName"] = x.lastName;
    }
}

    extern "C" { 
        namespace ereol {
#endif
            Contributor*  ereol_Contributor_instantiate()
            {
                return new Contributor();
            }
            void ereol_Contributor_delete(Contributor* m)  
            { 
                delete m; 
            } 
            const char*  ereol_Contributor_getType(Contributor* m) 
            { return m->type.c_str(); } 
            void   ereol_Contributor_setType(Contributor* m,  const char* cp) 
            { m->type.assign(cp); }    
            const char*  ereol_Contributor_getComposedName(Contributor* m) 
            { return m->composedName.c_str(); } 
            void   ereol_Contributor_setComposedName(Contributor* m,  const char* cp) 
            { m->composedName.assign(cp); }    
            const char*  ereol_Contributor_getFirstName(Contributor* m) 
            { return m->firstName.c_str(); } 
            void   ereol_Contributor_setFirstName(Contributor* m,  const char* cp) 
            { m->firstName.assign(cp); }    
            const char*  ereol_Contributor_getLastName(Contributor* m) 
            { return m->lastName.c_str(); } 
            void   ereol_Contributor_setLastName(Contributor* m,  const char* cp) 
            { m->lastName.assign(cp); }                                        

#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 














