//
// Created by root on 1/29/22.
//

#include "Secrets.h"

Secrets::Secrets() {
    if(const char* apiKeyEnv = std::getenv("TEST_API_KEY")){
        Secrets::apiKey = apiKeyEnv;
    }
    if(const char* usernameEnv = std::getenv("TEST_USERNAME")){
        Secrets::username = usernameEnv;
    }
    if(const char* passwordEnv = std::getenv("TEST_PASSWORD")){
        Secrets::password = passwordEnv;
    }
    if(const char* libraryEnv = std::getenv("TEST_LIBRARY")){
        Secrets::library = libraryEnv;
    }
}