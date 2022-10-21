#ifndef EREOLENWRAPPER_AUTH_H
#define EREOLENWRAPPER_AUTH_H

#include "ApiEnv.h"
#include "model/Token.h"
#include "model/Response.h"
#include <string>
#include <optional>
namespace ereol {
    class Auth {
    public:
        static ereol::Response<ereol::Token> authenticate(const std::string& username, const std::string& password, const ereol::Library& library);
        static ereol::Response<bool> deauthenticate(ereol::Token& token);
        static ereol::Response<bool> isAuthenticated(ereol::Token& token);
    };
}
#endif //EREOLENWRAPPER_AUTH_H
