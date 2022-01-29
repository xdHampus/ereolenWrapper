//
// Created by work on 1/29/22.
//

#include "Auth.h"
#include "ApiEnv.h"
#include <cpr/cpr.h>
#include <iostream>

std::optional<ereol::Token> ereol::Auth::authenticate(std::string username, std::string password, std::string library, std::string apiKey) {
    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{"This is raw POST data"},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Parameters{{"anon", "true"}, {"key", "value"}});


    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;
    std::cout << r.text << std::endl;

    if(r.status_code == 200) {

        ereol::Token token;
        token.timeFetched = 9999;
        token.token = r.text;

        return {token};
    } else {
        return {};
    }
}

std::optional<ereol::Token> ereol::Auth::authenticate(std::string username, std::string password, std::string library) {
    return ereol::Auth::authenticate(username, password, library, ereol::Auth::apiKey);
}

bool ereol::Auth::deauthenticate(ereol::Token token) {
    return false;
}

bool ereol::Auth::isAuthenticated(ereol::Token token) {
    return false;
}


