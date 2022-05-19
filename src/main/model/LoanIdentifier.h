//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_LOANIDENTIFIER_H
#define EREOLENWRAPPER_LOANIDENTIFIER_H
#ifdef __cplusplus 
#include <string>
namespace ereol {
    struct LoanIdentifier {
        std::string identifier;
        std::string isbn;
    };
    void from_json(const std::string  &s, ereol::LoanIdentifier& x);
    void to_json(std::string & s, const ereol::LoanIdentifier & x);       
#else
//struct
typedef struct LoanIdentifier LoanIdentifier;
LoanIdentifier*  ereol_LoanIdentifier_instantiate(); 
void ereol_LoanIdentifier_delete(LoanIdentifier* m);  
//identifier
const char*  ereol_LoanIdentifier_getIdentifier(LoanIdentifier* m); 
void   ereol_LoanIdentifier_setIdentifier(LoanIdentifier* m,  char* cp); 
//isbn
const char*  ereol_LoanIdentifier_getISBN(LoanIdentifier* m); 
void   ereol_LoanIdentifier_setISBN(LoanIdentifier* m,  char* cp); 
#endif
#ifdef __cplusplus 
}
#endif
#endif //EREOLENWRAPPER_LOANIDENTIFIER_H
