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
const char*  ereol_LoanHistorical_getType(LoanHistorical* m); 
void   ereol_LoanHistorical_setType(LoanHistorical* m, const char* cp); 
//composedName
const char*  ereol_LoanHistorical_getComposedName(LoanHistorical* m); 
void   ereol_LoanHistorical_setComposedName(LoanHistorical* m, const char* cp); 
//firstName
const char*  ereol_LoanHistorical_getFirstName(LoanHistorical* m); 
void   ereol_LoanHistorical_setFirstName(LoanHistorical* m, const char* cp); 
//lastName
const char*  ereol_LoanHistorical_getLastName(LoanHistorical* m); 
void   ereol_LoanHistorical_setLastName(LoanHistorical* m, const char* cp);   
#endif
#ifdef __cplusplus 
}
#endif

#endif //EREOLENWRAPPER_CONTRIBUTOR_H
