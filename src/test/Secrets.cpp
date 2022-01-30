//
// Created by root on 1/29/22.
//

#include "Secrets.h"


Secrets::Secrets() {
    if(const char* apiKeyEnv = std::getenv(Secrets::apiKeyEnvVar.c_str())){
        Secrets::apiKey = apiKeyEnv;
    }
    if(const char* usernameEnv = std::getenv(Secrets::usernameEnvVar.c_str())){
        Secrets::username = usernameEnv;
    }
    if(const char* passwordEnv = std::getenv(Secrets::passwordEnvVar.c_str())){
        Secrets::password = passwordEnv;
    }
    if(const char* libraryEnv = std::getenv(Secrets::libraryEnvVar.c_str())){
        Secrets::library = libraryEnv;
    }
}