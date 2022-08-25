#ifndef EREOLENWRAPPER_AUTH_H
#define EREOLENWRAPPER_AUTH_H

#include "ApiEnv.h"
#include "src/main/model/Token.h"
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
}
#endif //EREOLENWRAPPER_AUTH_H
