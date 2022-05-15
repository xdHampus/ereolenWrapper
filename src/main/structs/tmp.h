//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_LOANIDENTIFIER_H
#define EREOLENWRAPPER_LOANIDENTIFIER_H
#pragma

#ifdef __cplusplus 
#include <string>
namespace ereol {

    struct LoanIdentifier {
        std::string identifier;
        std::string isbn;
    };
#else
    struct LoanIdentifier;
#endif

#ifdef __cplusplus 
    extern "C" { 
#else
        const char*  ereol_LoanIdentifier_getIdentifier(  LoanIdentifier* m)  
        { return m->identifier.c_str(); }
        void   ereol_LoanIdentifier_setIdentifier(  LoanIdentifier* m,  char* cp)  
        { m->identifier.assign(cp); } 
        const char*  ereol_LoanIdentifier_getISBN(  LoanIdentifier* m)  
        { return m->isbn.c_str(); } 
        void   ereol_LoanIdentifier_setISBN(  LoanIdentifier* m,  char* cp)  
        { m->isbn.assign(cp); } 
        void ereol_LoanIdentifier_delete(  LoanIdentifier* m)  
        { 
            m->~LoanIdentifier();  
        } 
#endif  // __cplusplus 

#ifdef __cplusplus 
    } // extern "C" 
}
#endif  // __cplusplus 


#endif //EREOLENWRAPPER_LOANIDENTIFIER_H
