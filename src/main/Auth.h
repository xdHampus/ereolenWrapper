//
// Created by work on 1/29/22.
//

#ifndef EREOLENWRAPPER_AUTH_H
#define EREOLENWRAPPER_AUTH_H


#include <string>
#include <optional>
#include "ApiEnv.h"
#include "src/main/structs/Token.h"

namespace ereol {
    class Auth {
    private:
        inline static const std::string authMethod = "authenticate";
        inline static const std::string isAuthMethod = "isAuthenticated";
        inline static const std::string deAuthMethod = "deauthenticate";
    public:
        static std::optional<ereol::Token> authenticate(std::string username, std::string password, ereol::Library library);
        static bool deauthenticate(ereol::Token token);
        static bool isAuthenticated(ereol::Token token);
    };
}



#endif //EREOLENWRAPPER_AUTH_H
