//
// Created by work on 1/29/22.
//

#include "Auth.h"
#include "ApiEnv.h"
#include "src/main/structs/Library.h"
#include "src/main/structs/RpcPayload.h"
#include "src/main/structs/Token.h"
#ifdef __cplusplus 
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>


std::optional<ereol::Token> ereol::Auth::authenticate(std::string username, std::string password, ereol::Library library) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            ereol::Auth::authMethod,
            {
              ereol::ApiEnv::getApiKey(),
              ereol::ApiEnv::getAppVersion(),
              ereol::ApiEnv::getLanguage(),
              ereol::ApiEnv::getLibraryCode(library),
              username,
              password
            }
            );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}});

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>()) {
                ereol::Token token;
                token.timeFetched = 9999;
                token.sessid = r.cookies["PHPSESSID"];
                token.library = library;
                return {token};
            } else { //TODO: Incorrect credentials
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return {};
}

bool ereol::Auth::deauthenticate(ereol::Token token) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            ereol::Auth::deAuthMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library)
            }
    );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);


        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>()) {
                return true;
            } else { //TODO: SESSID not authenticated or incorrect
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return false;
}

bool ereol::Auth::isAuthenticated(ereol::Token token) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            ereol::Auth::isAuthMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library)
            }
    );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["data"].get<bool>()) {
                return true;
            } else { //TODO: SESSID not authenticated or incorrect
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return false;
}


extern "C" { 
    namespace ereol {
#endif
        Token*  ereol_Auth_authenticate(char* username, char* password, Library* library) {
            std::string sU(username);
            std::string sP(password);
            std::optional<Token> optToken = ereol::Auth::authenticate(sU, sP, *library);
            if(optToken.has_value()){
                return &optToken.value();
            } else {
                return nullptr;
            }
        }
        bool  ereol_Auth_deauthenticate(Token* token) {
            return ereol::Auth::deauthenticate(*token);

        }
        bool  ereol_Auth_isAuthenticated(Token* token) {
            return ereol::Auth::isAuthenticated(*token);
        }
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 