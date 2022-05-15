#ifndef EREOLENWRAPPER_LOANHISTORICAL_H
#define EREOLENWRAPPER_LOANHISTORICAL_H
#include "LoanIdentifier.h"
#ifdef __cplusplus 
#include <vector>
#include <string>
namespace ereol {
    struct LoanHistorical {
        ereol::LoanIdentifier loanIdentifier;
        std::string loanId;
        int loanDate;
        bool manuallyAdded;
        std::string title;
        std::string creator;
        std::string publicationDate;
        std::vector<std::string> materialTypes;
    };
#else
//struct
typedef struct LoanHistorical LoanHistorical;
LoanHistorical*  ereol_LoanHistorical_instantiate(); 
void ereol_LoanHistorical_delete(LoanHistorical* m);   
//loanIdentifier
LoanIdentifier*  ereol_LoanHistorical_getLoanIdentifier(LoanHistorical* m); 
void   ereol_LoanHistorical_setLoanIdentifier(LoanHistorical* m,  LoanIdentifier* identifier); 
//loanId
const char*  ereol_LoanHistorical_getLoanId(LoanHistorical* m); 
void   ereol_LoanHistorical_setLoanId(LoanHistorical* m,  char* cp); 
//loanDate
int  ereol_LoanHistorical_geLoanDate(LoanHistorical* m); 
void   ereol_LoanHistorical_setLoanDate(LoanHistorical* m,  int utc); 
//manuallyAdded
bool  ereol_LoanHistorical_getManuallyAdded(LoanHistorical* m); 
void   ereol_LoanHistorical_setManuallyAdded(LoanHistorical* m,  bool state); 
//title
const char*  ereol_LoanHistorical_getTitle(LoanHistorical* m); 
void   ereol_LoanHistorical_setTitle(LoanHistorical* m,  char* cp); 
//creator
const char*  ereol_LoanHistorical_getCreator(LoanHistorical* m); 
void   ereol_LoanHistorical_setCreator(LoanHistorical* m,  char* cp); 
//publicationDate
const char*  ereol_LoanHistorical_getPublicationDate(LoanHistorical* m); 
void   ereol_LoanHistorical_setPublicationDate(LoanHistorical* m,  char* cp); 
//materialTypes
const char**  ereol_LoanHistorical_getMaterialTypes(LoanHistorical* m); 
size_t ereol_LoanHistorical_getMaterialTypes_size(LoanHistorical* m); 
void ereol_LoanHistorical_getMaterialTypes_insert(LoanHistorical* m, char* x); 
void   ereol_LoanHistorical_setMaterialTypes(LoanHistorical* m,  char** arr, size_t n);    
#endif //end __cplusplus
#ifdef __cplusplus 
}
#endif //end __cplusplus

#endif //EREOLENWRAPPER_LOANHISTORICAL_H
