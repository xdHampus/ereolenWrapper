//
// Created by work on 1/29/22.
//
#include <gtest/gtest.h>
#include "Secrets.h"
#include "../main/Auth.h"
#include "../main/ApiEnv.h"
#include <optional>

class AuthTestHelper {
public:
    Secrets secrets;
    AuthTestHelper() {
        secrets = Secrets();
    }
};
AuthTestHelper authTH = AuthTestHelper();

TEST(AuthTest, AuthSucceeds) {
    ereol::ApiEnv::setRPC("http://localhost:5000/mock-rpc");

    std::optional<ereol::Library> optLibrary = ereol::ApiEnv::getLibraryFromCode(authTH.secrets.getLibrary());
    EXPECT_TRUE(optLibrary.has_value());

    std::optional<ereol::Token> optToken = ereol::Auth::authenticate(
            authTH.secrets.getUsername(),
            authTH.secrets.getPassword(),
            optLibrary.value());

    EXPECT_TRUE(optToken.has_value());
    if(optToken.has_value()){
        EXPECT_TRUE(ereol::Auth::isAuthenticated(optToken.value()));
        EXPECT_EQ(optLibrary.value(), optToken.value().library);
    }
}

TEST(AuthTest, AuthFails) {
    std::optional<ereol::Token> optToken = ereol::Auth::authenticate("user", "pass", ereol::Library::GREVE);
    EXPECT_FALSE(optToken.has_value());
}

TEST(AuthTest, DeAuthSucceeds) {
    std::optional<ereol::Library> optLibrary = ereol::ApiEnv::getLibraryFromCode(authTH.secrets.getLibrary());
    EXPECT_TRUE(optLibrary.has_value());

    std::optional<ereol::Token> optToken = ereol::Auth::authenticate(
            authTH.secrets.getUsername(),
            authTH.secrets.getPassword(),
            optLibrary.value());

    EXPECT_TRUE(optToken.has_value());
    if(optToken.has_value()){
        EXPECT_TRUE(ereol::Auth::isAuthenticated(optToken.value()));
        EXPECT_TRUE(ereol::Auth::deauthenticate(optToken.value()));
        EXPECT_FALSE(ereol::Auth::isAuthenticated(optToken.value()));
    }
}







