//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_TOKEN_H
#define EREOLENWRAPPER_TOKEN_H

#include "Library.h"
#ifdef __cplusplus 
#include <string>
namespace ereol {
    struct Token {
        uint64_t timeFetched;
        std::string sessid;
        std::string expirationDate;
        ereol::Library library;
    };
#else
//struct
typedef struct Token Token;
Token*  ereol_Token_instantiate(); 
void ereol_Token_delete(Token* m);      
//timeFetched
uint64_t  ereol_Token_getTimeFetched(Token* m); 
void   ereol_Token_setTimeFetched(Token* m,  uint64_t utc); 
//sessid
const char*  ereol_Token_getSessid(Token* m); 
void   ereol_Token_setSessid(Token* m,  const char* cp); 
//expirationDate
const char*  ereol_Token_getExpirationDate(Token* m); 
void   ereol_Token_setExpirationDate(Token* m, const char* cp); 
//library
enum Library  ereol_Token_getLibrary(Token* m); 
void   ereol_Token_setLibrary(Token* m, enum Library library); 
#endif
#ifdef __cplusplus 
}
#endif


#endif //EREOLENWRAPPER_TOKEN_H