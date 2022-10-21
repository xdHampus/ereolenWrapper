#include "Auth.h"
#include "ApiEnv.h"
#include "src/main/model/Library.h"
#include "src/main/model/RpcPayload.h"
#include "src/main/model/Token.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "src/main/util/ErrorResponse.h"
#include "src/main/util/ApiCaller.h"
#ifdef COMPILE_LUA
#include "lua/LuaInterface.h"
#include "lua/ResponseLua.h"
#endif


const std::string authMethod   = "authenticate";
const std::string isAuthMethod = "isAuthenticated";
const std::string deAuthMethod = "deauthenticate";

ereol::Response<ereol::Token> ereol::Auth::authenticate(const std::string& username,const std::string& password,const ereol::Library& library) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            authMethod,
            {
              ereol::ApiEnv::getApiKey(),
              ereol::ApiEnv::getAppVersion(),
              ereol::ApiEnv::getLanguage(),
              ereol::ApiEnv::getLibraryCode(library),
              username,
              password
            }
            );

    cpr::Response r = ereol::ApiCaller::requestPost(payloadJson);

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>()) {
                ereol::Token token;
                token.timeFetched = 9999; //TODO: Get time at this instance
                token.sessid = r.cookies["PHPSESSID"];
                token.library = library;
                return Response<Token>(token);
            } else { return ereol::ErrorResponse::incorrectCredentials<Token>(); }
        } else { return ereol::ErrorResponse::genericErrorAPI<Token>({}); }
    } else { return ereol::ErrorResponse::genericErrorHTTP<Token>({}); }
}

ereol::Response<bool> ereol::Auth::deauthenticate(ereol::Token& token) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadJSON(deAuthMethod, token.library);
    cpr::Response r = ereol::ApiCaller::requestPost(payloadJson, token);

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);
        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>()) {
                return Response<bool>(true);
            } else { return ereol::ErrorResponse::invalidSessionID<bool>(); }
        } else { return ereol::ErrorResponse::genericErrorAPI<bool>({}); }
    } else { return ereol::ErrorResponse::genericErrorHTTP<bool>({}); }
}

ereol::Response<bool> ereol::Auth::isAuthenticated(ereol::Token& token) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadJSON(isAuthMethod, token.library);
    cpr::Response r = ereol::ApiCaller::requestPost(payloadJson, token);

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["data"].get<bool>()) {
                return Response<bool>(true);
            } else { return ereol::ErrorResponse::invalidSessionID<bool>(); }
        } else { return ereol::ErrorResponse::genericErrorAPI<bool>({}); }
    } else { return ereol::ErrorResponse::genericErrorHTTP<bool>({}); }
}




#ifdef COMPILE_LUA
void ereol::luaRegisterAuth(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Auth>("Auth")
            .addStaticFunction ("authenticate",
                std::function<ereol::Response<ereol::Token>(const std::string&, const std::string&, int)>(
                [](const std::string& username,const std::string& password, int library){
                    return ereol::Auth::authenticate(username,password,static_cast<ereol::Library>(library));
                })
            )
            .addStaticFunction ("deauthenticate", ereol::Auth::deauthenticate)
            .addStaticFunction ("isAuthenticated", ereol::Auth::isAuthenticated)
        .endClass()
    .endNamespace();
}
#endif