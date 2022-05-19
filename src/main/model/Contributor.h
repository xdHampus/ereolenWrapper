#ifndef EREOLENWRAPPER_CONTRIBUTOR_H
#define EREOLENWRAPPER_CONTRIBUTOR_H

#ifdef __cplusplus 
#include <string>
namespace ereol {
    struct Contributor {
        std::string type;
        std::string composedName;
        std::string firstName;
        std::string lastName;
    };
    void from_json(const std::string  &s, ereol::Contributor& x);
    void to_json(std::string & s, const ereol::Contributor & x);    
#else
//struct
typedef struct Contributor Contributor;
Contributor*  ereol_Contributor_instantiate(); 
void ereol_Contributor_delete(Contributor* m);    
//type
const char*  ereol_Contributor_getType(Contributor* m); 
void   ereol_Contributor_setType(Contributor* m, const char* cp); 
//composedName
const char*  ereol_Contributor_getComposedName(Contributor* m); 
void   ereol_Contributor_setComposedName(Contributor* m, const char* cp); 
//firstName
const char*  ereol_Contributor_getFirstName(Contributor* m); 
void   ereol_Contributor_setFirstName(Contributor* m, const char* cp); 
//lastName
const char*  ereol_Contributor_getLastName(Contributor* m); 
void   ereol_Contributor_setLastName(Contributor* m, const char* cp);   
#endif
#ifdef __cplusplus 
}
#endif

#endif //EREOLENWRAPPER_CONTRIBUTOR_H
