#include "Token.h"
#ifdef __cplusplus 
    extern "C" { 
        namespace ereol {
#endif
            Token*  ereol_Token_instantiate() 
            {
                return new Token();
            }
            void ereol_Token_delete(Token* m)    
            { 
                delete m;
            } 
            uint64_t  ereol_Token_getTimeFetched(Token* m) 
            { return m->timeFetched; } 
            void   ereol_Token_setTimeFetched(Token* m,  uint64_t utc) 
            { m->timeFetched = utc; }             
            const char*  ereol_Token_getSessid(Token* m) 
            { return m->sessid.c_str(); } 
            void   ereol_Token_setSessid(Token* m,  const char* cp) 
            { m->sessid.assign(cp); } 
            const char*  ereol_Token_getExpirationDate(Token* m) 
            { return m->expirationDate.c_str(); } 
            void   ereol_Token_setExpirationDate(Token* m, const char* cp) 
            { m->expirationDate.assign(cp); }             
            Library  ereol_Token_getLibrary(Token* m) 
            { return m->library; }
            void   ereol_Token_setLibrary(Token* m,  Library library) 
            { m->library = library; }              
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 
