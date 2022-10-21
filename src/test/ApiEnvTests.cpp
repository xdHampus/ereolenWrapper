#include <gtest/gtest.h>
#include <optional>
#include <string>
#include "../main/ApiEnv.h"

TEST(ApiEnvTest, LibraryConversionFromStringSucceeds) {
    std::string correctLibraryCode = "odensebib";

    std::optional<ereol::Library> optLibrary = ereol::ApiEnv::getLibraryFromCode(correctLibraryCode);
    EXPECT_TRUE(optLibrary.has_value());
    if(optLibrary.has_value()){
        EXPECT_STREQ(correctLibraryCode.c_str(), ereol::ApiEnv::getLibraryCode(optLibrary.value()).c_str());
    }
}
TEST(ApiEnvTest, LibraryConversionFromStringFails) {
    std::string incorrectLibraryCode = "nowhere";

    std::optional<ereol::Library> optLibrary = ereol::ApiEnv::getLibraryFromCode(incorrectLibraryCode);
    EXPECT_FALSE(optLibrary.has_value());
}

TEST(ApiEnvTest, LibrariesHaveNameAndCode) {
    for ( int i = 0; i != ereol::ApiEnv::getLibraryCount(); i++ )
    {
        ereol::Library library = static_cast<ereol::Library>(i);
        EXPECT_TRUE(ereol::ApiEnv::getLibraryCode(library).length() > 0);
        EXPECT_TRUE(ereol::ApiEnv::getLibraryName(library).length() > 0);
    }
}