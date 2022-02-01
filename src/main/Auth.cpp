//
// Created by work on 1/29/22.
//

#include "Auth.h"
#include "ApiEnv.h"
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

