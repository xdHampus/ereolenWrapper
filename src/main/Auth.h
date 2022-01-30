//
// Created by work on 1/29/22.
//

#ifndef EREOLENWRAPPER_AUTH_H
#define EREOLENWRAPPER_AUTH_H


#include <string>
#include <optional>

namespace ereol {
    struct Token {
        int timeFetched;
        std::string sessid;
        std::string library;
    };
    class Auth {
    private:
        inline static const std::string authMethod = "authenticate";
        inline static const std::string isAuthMethod = "isAuthenticated";
        inline static const std::string deAuthMethod = "deauthenticate";

    public:
        static std::optional<Token> authenticate(std::string username, std::string password, std::string library);
        static bool deauthenticate(Token token);
        static bool isAuthenticated(Token token);
    };
}



#endif //EREOLENWRAPPER_AUTH_H
