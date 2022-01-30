//
// Created by work on 1/29/22.
//
#include <gtest/gtest.h>
#include <optional>
#include "../main/Auth.h"
#include "Secrets.h"

Secrets secrets = Secrets();

TEST(AuthTest, AuthSucceeds) {
    std::optional<ereol::Token> optToken = ereol::Auth::authenticate(secrets.getUsername(), secrets.getPassword(), secrets.getLibrary());
    EXPECT_TRUE(optToken.has_value());
    if(optToken.has_value()){
        EXPECT_TRUE(ereol::Auth::isAuthenticated(optToken.value()));
        EXPECT_EQ(secrets.getLibrary(), optToken.value().library);
    }
}

TEST(AuthTest, AuthFails) {
    std::optional<ereol::Token> optToken = ereol::Auth::authenticate("user", "pass", "nowhere");
    EXPECT_FALSE(optToken.has_value());
}

TEST(AuthTest, DeAuthSucceeds) {
    std::optional<ereol::Token> optToken = ereol::Auth::authenticate(secrets.getUsername(), secrets.getPassword(), secrets.getLibrary());
    EXPECT_TRUE(optToken.has_value());
    if(optToken.has_value()){
        EXPECT_TRUE(ereol::Auth::isAuthenticated(optToken.value()));
        EXPECT_TRUE(ereol::Auth::deauthenticate(optToken.value()));
        EXPECT_FALSE(ereol::Auth::isAuthenticated(optToken.value()));
    }
}
TEST(AuthTest, DeAuthFails) {
    ereol::Token token;
    token.sessid = "abcjasha22hahdja2";
    token.library = "nowhere";
    EXPECT_FALSE(ereol::Auth::deauthenticate(token));
}






