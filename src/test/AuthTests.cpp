#include <gtest/gtest.h>
#include "BaseTestHelper.h"
#include "../main/Auth.h"
#include "../main/ApiEnv.h"
#include <optional>

class AuthTestHelper : public BaseTestHelper {
public:
    AuthTestHelper() = default;
};
AuthTestHelper authTH = AuthTestHelper();

TEST(AuthTest, AuthSucceeds) {
    authTH.ensureLoaded();

    std::optional<ereol::Library> optLibrary = ereol::ApiEnv::getLibraryFromCode(authTH.getLibrary());
    EXPECT_TRUE(optLibrary.has_value());

    ereol::Response<ereol::Token> optToken = ereol::Auth::authenticate(
            authTH.getUsername(),
            authTH.getPassword(),
            optLibrary.value());

    EXPECT_TRUE(optToken.success());
    EXPECT_TRUE(optToken.data().has_value());
    if(optToken.data().has_value()){
        EXPECT_TRUE(ereol::Auth::isAuthenticated((ereol::Token &) optToken.data().value()).success());
        EXPECT_EQ(optLibrary.value(), optToken.data().value().library);
    }
}

TEST(AuthTest, AuthFails) {
    ereol::Response<ereol::Token> optToken = ereol::Auth::authenticate("user", "pass", ereol::Library::GREVE);
    EXPECT_FALSE(optToken.success());
    EXPECT_FALSE(optToken.data().has_value());
}

TEST(AuthTest, DeAuthSucceeds) {
    std::optional<ereol::Library> optLibrary = ereol::ApiEnv::getLibraryFromCode(authTH.getLibrary());
    EXPECT_TRUE(optLibrary.has_value());

    ereol::Response<ereol::Token> optToken = ereol::Auth::authenticate(
            authTH.getUsername(),
            authTH.getPassword(),
            optLibrary.value());

    EXPECT_TRUE(optToken.success());
    EXPECT_TRUE(optToken.data().has_value());
    if(optToken.data().has_value()){
        EXPECT_TRUE(ereol::Auth::isAuthenticated((ereol::Token &) optToken.data().value()).success());
        EXPECT_TRUE(ereol::Auth::deauthenticate((ereol::Token &) optToken.data().value()).success());
        EXPECT_FALSE(ereol::Auth::isAuthenticated((ereol::Token &) optToken.data().value()).success());
    }
}







