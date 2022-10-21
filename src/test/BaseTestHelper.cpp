#include "BaseTestHelper.h"
#include "src/main/ApiEnv.h"
#include "src/main/Auth.h"
#include <gtest/gtest.h>


BaseTestHelper::BaseTestHelper() {
    if(const char* apiKeyEnv = std::getenv("TEST_API_KEY")){
        BaseTestHelper::apiKey = apiKeyEnv;
    }
    if(const char* usernameEnv = std::getenv("TEST_USERNAME")){
        BaseTestHelper::username = usernameEnv;
    }
    if(const char* passwordEnv = std::getenv("TEST_PASSWORD")){
        BaseTestHelper::password = passwordEnv;
    }
    if(const char* libraryEnv = std::getenv("TEST_LIBRARY")){
        BaseTestHelper::library = libraryEnv;
    }
}

void BaseTestHelper::ensureLoaded() {
    if(!loaded){
        ereol::ApiEnv::setRPC("http://localhost:5000/mock-rpc");
        optLibrary = ereol::ApiEnv::getLibraryFromCode(getLibrary());
        if(optLibrary.has_value()){
            optToken = ereol::Auth::authenticate(
                    getUsername(),
                    getPassword(),
                    optLibrary.value()).data();
        }
        loaded = true;
    }
}

void BaseTestHelper::tryCompare(std::optional<std::string> &expected, std::optional<std::string> &actual){
    EXPECT_EQ(expected.has_value(), actual.has_value());
    if(expected.has_value() && actual.has_value()){
        EXPECT_STREQ(expected.value().c_str(), actual.value().c_str());
    }
}
void BaseTestHelper::tryCompare(std::optional<std::vector<std::string>> &expected, std::optional<std::vector<std::string>> &actual){
    EXPECT_EQ(expected.has_value(), actual.has_value());
    if(expected.has_value() && actual.has_value()){
        EXPECT_EQ(expected.value().size(), actual.value().size());
        if(expected.value().empty()){
            return;
        }
        int i = 0;
        for (const auto &actualElement : actual.value()) {
            EXPECT_STREQ(expected.value().at(i).c_str(), actualElement.c_str());
            i++;
        }
    }
}
void BaseTestHelper::tryCompare(std::optional<std::vector<ereol::Contributor>> &expected, std::optional<std::vector<ereol::Contributor>> &actual){
    EXPECT_EQ(expected.has_value(), actual.has_value());
    if(expected.has_value() && actual.has_value()){
        EXPECT_EQ(expected.value().size(), actual.value().size());
        if(expected.value().empty()){
            return;
        }
        int i = 0;
        for (const auto &actualElement : actual.value()) {
            EXPECT_STREQ(expected.value().at(i).type.c_str(), actualElement.type.c_str());
            EXPECT_STREQ(expected.value().at(i).composedName.c_str(), actualElement.composedName.c_str());
            EXPECT_STREQ(expected.value().at(i).firstName.c_str(), actualElement.firstName.c_str());
            EXPECT_STREQ(expected.value().at(i).lastName.c_str(), actualElement.lastName.c_str());
            i++;
        }
    }
}
void BaseTestHelper::tryCompare(ereol::Record &expected, ereol::Record &actual){

    EXPECT_STREQ(expected.loanIdentifier.identifier.c_str(), actual.loanIdentifier.identifier.c_str());
    EXPECT_STREQ(expected.loanIdentifier.isbn.c_str(), actual.loanIdentifier.isbn.c_str());

    EXPECT_STREQ(expected.title.c_str(), actual.title.c_str());
    EXPECT_STREQ(expected.publisher.c_str(), actual.publisher.c_str());
    EXPECT_STREQ(expected.description.c_str(), actual.description.c_str());
    EXPECT_STREQ(expected.language.c_str(), actual.language.c_str());
    EXPECT_STREQ(expected.mediaType.c_str(), actual.mediaType.c_str());

    EXPECT_EQ(expected.createdDate, actual.createdDate);
    EXPECT_EQ(expected.updatedDate, actual.updatedDate);
    EXPECT_EQ(expected.firstPublished, actual.firstPublished);
    EXPECT_EQ(expected.duration, actual.duration);

    tryCompare(expected.recordType, actual.recordType);
    tryCompare(expected.cover, actual.cover);
    tryCompare(expected.phid, actual.phid);
    tryCompare(expected.format, actual.format);
    tryCompare(expected.thumbnail, actual.thumbnail);
    tryCompare(expected.abstract, actual.abstract);
    tryCompare(expected.year, actual.year);
    tryCompare(expected.edition, actual.edition);
    tryCompare(expected.shelfmark, actual.shelfmark);
    tryCompare(expected.seriesPart, actual.seriesPart);
    tryCompare(expected.subscription, actual.subscription);
    tryCompare(expected.eReolenGlobalUrl, actual.eReolenGlobalUrl);

    tryCompare(expected.contributors, actual.contributors);
    tryCompare(expected.creators, actual.creators);
    tryCompare(expected.series, actual.series);
    tryCompare(expected.subjects, actual.subjects);
    tryCompare(expected.types, actual.types);
}

void BaseTestHelper::tryCompare(ereol::PageResult &expected, ereol::PageResult &actual) {
    EXPECT_EQ(expected.count, actual.count);
    EXPECT_EQ(expected.more, actual.more);

    EXPECT_EQ(expected.data.size(), actual.data.size());
    if((!expected.data.empty() && !actual.data.empty()) && (expected.data.size() == actual.data.size())){
        for (int i = 0; i < expected.data.size(); ++i) {
            EXPECT_EQ(expected.data.at(i).size(), actual.data.at(i).size());
            if((!expected.data.at(i).empty() && !actual.data.at(i).empty()) && (expected.data.at(i).size() == actual.data.at(i).size())) {
                for (int j = 0; j < expected.data.at(i).size(); ++j) {
                    tryCompare(expected.data.at(i).at(j), actual.data.at(i).at(j));
                }
            }
        }
    }
    EXPECT_EQ(expected.facets.size(), actual.facets.size());
    if(!expected.facets.empty() && !actual.facets.empty()){

    }
}

void BaseTestHelper::tryCompare(ereol::Review &expected, ereol::Review &actual) {
    EXPECT_STREQ(expected.source.c_str(), actual.source.c_str());
    EXPECT_STREQ(expected.subTitle.c_str(), actual.subTitle.c_str());
    EXPECT_STREQ(expected.url.c_str(), actual.url.c_str());
}
