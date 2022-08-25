//
// Created by root on 1/29/22.
//

#ifndef EREOLENWRAPPER_BASETESTHELPER_H
#define EREOLENWRAPPER_BASETESTHELPER_H

#include <string>
#include "src/main/model/Record.h"
#include "src/main/model/Library.h"
#include "src/main/model/Token.h"
#include "src/main/model/PageResult.h"
#include "src/main/model/Review.h"

class BaseTestHelper {
private:
    std::string apiKey;
    std::string username;
    std::string password;
    std::string library;
public:
    bool loaded = false;
    std::optional<ereol::Library> optLibrary = {};
    std::optional<ereol::Token> optToken = {};

    BaseTestHelper();

    std::string getApiKey() {return apiKey;}
    std::string getUsername() {return username;}
    std::string getPassword() {return password;}
    std::string getLibrary() {return library;}

    void ensureLoaded();
    static void tryCompare(std::optional<std::string> &expected, std::optional<std::string> &actual);
    static void tryCompare(std::optional<std::vector<std::string>> &expected, std::optional<std::vector<std::string>> &actual);
    static void tryCompare(std::optional<std::vector<ereol::Contributor>> &expected, std::optional<std::vector<ereol::Contributor>> &actual);
    static void tryCompare(ereol::Record &expected, ereol::Record &actual);
    static void tryCompare(ereol::Review &expected, ereol::Review &actual);
    static void tryCompare(ereol::PageResult &expected, ereol::PageResult &actual);

};


#endif //EREOLENWRAPPER_BASETESTHELPER_H
