#ifndef EREOLENWRAPPER_AUTH_H
#define EREOLENWRAPPER_AUTH_H

#include "ApiEnv.h"
#include "src/main/model/Token.h"
#ifdef __cplusplus 
#include <string>
#include <optional>
namespace ereol {
    class Auth {
    private:
        static const std::string authMethod;
        static const std::string isAuthMethod;
        static const std::string deAuthMethod;
    public:
        static std::optional<ereol::Token> authenticate(std::string username, std::string password, ereol::Library library);
        static bool deauthenticate(ereol::Token token);
        static bool isAuthenticated(ereol::Token token);
    };

#else
Token*  ereol_Auth_authenticate(char* username, char* password, Library* library); 
bool  ereol_Auth_deauthenticate(Token* token); 
bool  ereol_Auth_isAuthenticated(Token* library); 
#endif
#ifdef __cplusplus 
}
#endif
#endif //EREOLENWRAPPER_AUTH_H
