//
// Created by root on 1/29/22.
//

#ifndef EREOLENWRAPPER_SECRETS_H
#define EREOLENWRAPPER_SECRETS_H

#include <string>

class Secrets {
private:
    inline static const std::string apiKeyEnvVar = "TEST_API_KEY";
    inline static const std::string usernameEnvVar = "TEST_USERNAME";
    inline static const std::string passwordEnvVar = "TEST_PASSWORD";
    inline static const std::string libraryEnvVar = "TEST_LIBRARY";
    std::string apiKey;
    std::string username;
    std::string password;
    std::string library;
public:
    Secrets();

    std::string getApiKey() {return apiKey;}
    std::string getUsername() {return username;}
    std::string getPassword() {return password;}
    std::string getLibrary() {return library;}
};


#endif //EREOLENWRAPPER_SECRETS_H
