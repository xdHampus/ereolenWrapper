//
// Created by root on 1/30/22.
//

// prefix for disabling tests DISABLED_

#include <gtest/gtest.h>
#include "Secrets.h"
#include "../main/Auth.h"
#include "../main/ApiEnv.h"
#include "../main/Profile.h"
#include <optional>
#include <vector>

//TODO: Change integrations test to rely on mock server such that state from eReolen.dk is avoided
class ProfileTestHelper {
public:

    std::vector<ereol::LoanActive> loansMockData = {
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcyNjE1MzY2OCIsImMiOiJlcmVvbGVuIn0=",
                            "9788726153668"
                    },
                    "3002cc7e-90d4-4f67-bc76-de62590423db",
                    "7ab14d7f-4b75-4f9b-b3d5-ffffb7422cd8",
                    1643587442,
                    1646179441,
                    "http://acs.pubhub.dk:8080/fulfillment/URLLink.acsm?action=enterloan&ordersource=Pubhub&orderid=7ab14d7f-4b75-4f9b-b3d5-ffffb7422cd8&resid=urn%3Auuid%3A8fcc0bc8-e75e-450a-a969-c292a0b478f0&rights=%24lat%231646175841%24&gbauthdate=01%2f30%2f2022+23%3a04+UTC&dateval=1643587441&gblver=4&auth=6ba3d8b243bef18e4c5c4a6575ffc83aeb6b7482",
                    true
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODc2NDQ4MDkyNCIsImMiOiJuZXRseWRib2cifQ==",
                            "9788764480924"
                    },
                    "cb39652b-204c-445a-b68c-04b6a953110f",
                    "2dc56e71-bc6e-4772-b360-f4556af7e056",
                    1643587904,
                    1646179903,
                    "https://download.pubhub.dk/audio/Download.ashx?cvoid=2dc56e71-bc6e-4772-b360-f4556af7e056",
                    false
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcyODExNzg1OSIsImMiOiJuZXRseWRib2cifQ==",
                            "9788728117859"
                    },
                    "f0b234b2-adf4-4a12-abbe-fd5b817748ce",
                    "fa702b8b-372b-4c7b-a534-a904bf94d5fb",
                    1643588494,
                    1646180493,
                    "https://download.pubhub.dk/audio/Download.ashx?cvoid=fa702b8b-372b-4c7b-a534-a904bf94d5fb",
                    true
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcwMjMxMjYyMSIsImMiOiJlcmVvbGVuIn0=",
                            "9788702312621"
                    },
                    "18553271-0aa7-4626-ba00-cd7f484194a4",
                    "0379b0c3-b2d6-406c-aef6-70a77b44ff2c",
                    1643588625,
                    1646180624,
                    "http://acs.pubhub.dk:8080/fulfillment/URLLink.acsm?action=enterloan&ordersource=Pubhub&orderid=0379b0c3-b2d6-406c-aef6-70a77b44ff2c&resid=urn%3Auuid%3A39369da7-a3d5-4974-b358-3f72b0344880&rights=%24lat%231646177024%24&gbauthdate=01%2f30%2f2022+23%3a23+UTC&dateval=1643588624&gblver=4&auth=a95243dee303d4a0ab7bb85ec2b5a6b612c99f65",
                    false
            }

    };
    std::vector<ereol::ChecklistItem> checklistMockData = {
            {
                ereol::LoanIdentifier{
                        "eyJpIjoiOTc4ODcwMjA5NjQwOCIsImMiOiJlcmVvbGVuIn0=",
                        "9788702096408",
                },
                1643584514
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODc5OTg2Mzc5MiIsImMiOiJlcmVvbGVuIn0=",
                            "9788799863792",
                    },
                    1643584466
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODc5MzczNzI3MyIsImMiOiJlcmVvbGVuIn0=",
                            "9788793737273",
                    },
                    1643584445
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcyODIxMzIzMCIsImMiOiJuZXRseWRib2cifQ==",
                            "9788728213230",
                    },
                    1643584316
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcyNjE0MTM0NCIsImMiOiJuZXRseWRib2cifQ==",
                            "9788726141344",
                    },
                    1643583885
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcwMjE5MTI3MSIsImMiOiJlcmVvbGVuIn0=",
                            "9788702191271",
                    },
                    1643583461
            },

    };
    std::vector<ereol::Reservation> reservationsMockData = {
            {
                ereol::LoanIdentifier{
                    "eyJpIjoiOTc4MTYyMzM3MjE5NCIsImMiOiJuZXRseWRib2cifQ==",
                    "9781623372194",
                },
                "9c0ede52-9e7c-4ad1-9795-9e58c7753f42",
                "queued",
                1643584290,
                -1,
                1651270017
            }
    };
    std::vector<ereol::LoanHistorical> loanHistoryMockData = {
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcwMjMxMjYyMSIsInMiOiI4NzA5NzAtYmFzaXM6NjE2ODQ4OTEifQ==",
                            "9788702312621"
                    },
                    "023a64382e6d8611b31506bb810d997abcca8f1aefd35bfe9a77c2ab4eda16f2",
                    1643588625,
                    false,
                    "Pan",
                    "Knut Hamsun",
                    "2021",
                    std::vector<std::string> {"Ebog"}
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcyODExNzg1OSIsInMiOiI4NzA5NzAtYmFzaXM6NjE2OTk5NTMifQ==",
                            "9788728117859"
                    },
                    "b963fffcdec03276228276ba7a5cc938d85cf16a7382accc36c54def37a208b8",
                    1643588494,
                    false,
                    "Slaget om Stalingrad",
                    "Troels Ussing",
                    "2021",
                    std::vector<std::string> {"Lydbog (net)"}
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODc2NDQ4MDkyNCIsInMiOiI4NzA5NzAtYmFzaXM6NjE3NDYwMDUifQ==",
                            "9788764480924"
                    },
                    "ea45589fbaf653a0dd990ed70c57afe282a9aff2511609c0689c55e992c6ccab",
                    1643587904,
                    false,
                    "Mord på Bretagnes kyst",
                    "Jean-Luc Bannalec",
                    "2021",
                    std::vector<std::string> {"Lydbog (net)"}
            },
            {
                    ereol::LoanIdentifier{
                            "eyJpIjoiOTc4ODcyNjE1MzY2OCIsInMiOiI4NzA5NzAtYmFzaXM6NDg5MDA3NDcifQ==",
                            "9788726153668"
                    },
                    "bf27a2896c2530f5199df78b110a1ce698d67ff99229c6653affd3634586798c",
                    1643587442,
                    false,
                    "Forvandlingen",
                    "Franz Kafka",
                    "2020",
                    std::vector<std::string> {"Ebog"}
            }

    };

    Secrets secrets;
    std::optional<ereol::Library> optLibrary = {};
    std::optional<ereol::Token> optToken = {};
    ProfileTestHelper() {
        secrets = Secrets();
        optLibrary = ereol::ApiEnv::getLibraryFromCode(secrets.getLibrary());
        if(optLibrary.has_value()){
            optToken = ereol::Auth::authenticate(
                    secrets.getUsername(),
                    secrets.getPassword(),
                    optLibrary.value());
        }
    };
};
ProfileTestHelper profileTH = ProfileTestHelper();


TEST(ProfileTest, DISABLED_TestLibProfile){
    ereol::Library library = ereol::Library::ALLEROED;
    int expectedMaxConcurrentLoansPerBorrower = 10;
    int expectedMaxConcurrentReservationsPerBorrower = 3;
    int expectedMaxConcurrentAudioLoansPerBorrower = 10;
    int expectedMaxConcurrentAudioReservationsPerBorrower = 3;

    std::optional<ereol::LibraryProfile> optLibraryProfile = ereol::Profile::getLibraryProfile(library);

    EXPECT_TRUE(optLibraryProfile.has_value());
    if(optLibraryProfile.has_value()){
        ereol::LibraryProfile profile = optLibraryProfile.value();
        EXPECT_EQ(expectedMaxConcurrentLoansPerBorrower, profile.maxConcurrentLoansPerBorrower);
        EXPECT_EQ(expectedMaxConcurrentReservationsPerBorrower, profile.maxConcurrentReservationsPerBorrower);
        EXPECT_EQ(expectedMaxConcurrentAudioLoansPerBorrower, profile.maxConcurrentAudioLoansPerBorrower);
        EXPECT_EQ(expectedMaxConcurrentAudioReservationsPerBorrower, profile.maxConcurrentAudioReservationsPerBorrower);
    }

}

//TODO: Add DISABLED_ prefix to disable tests when eReolen state inevitably changes
TEST(ProfileTest, DISABLED_GetLoansTest) {
    EXPECT_TRUE(profileTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(profileTH.optToken.value()));

    std::optional<std::vector<ereol::LoanActive>> optResults = ereol::Profile::getLoans(profileTH.optToken.value());
    EXPECT_TRUE(optResults.has_value());
    if(optResults.has_value()){
        int mockSize = profileTH.loansMockData.size();
        int i = 0;
        for (const auto &result : optResults.value()){
            EXPECT_TRUE(i < mockSize);
            ereol::LoanActive mockResult = profileTH.loansMockData.at(i);

            EXPECT_STREQ(mockResult.loanIdentifier.identifier.c_str(), result.loanIdentifier.identifier.c_str());

            EXPECT_STREQ(mockResult.loanIdentifier.isbn.c_str(), result.loanIdentifier.isbn.c_str());
            EXPECT_STREQ(mockResult.downloadUrl.c_str(), result.downloadUrl.c_str());
            EXPECT_STREQ(mockResult.internalOrderNumber.c_str(), result.internalOrderNumber.c_str());
            EXPECT_STREQ(mockResult.retailerOrderNumber.c_str(), result.retailerOrderNumber.c_str());
            EXPECT_EQ(mockResult.expireDate, result.expireDate);
            EXPECT_EQ(mockResult.orderDate, result.orderDate);
            EXPECT_EQ(mockResult.isSubscription, result.isSubscription);
            i++;
        }
    }

}
TEST(ProfileTest, DISABLED_GetChecklistTest) {
    EXPECT_TRUE(profileTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(profileTH.optToken.value()));

    std::optional<std::vector<ereol::ChecklistItem>> optResults = ereol::Profile::getCheckList(profileTH.optToken.value());
    EXPECT_TRUE(optResults.has_value());
    if(optResults.has_value()){
        int mockSize = profileTH.checklistMockData.size();
        int i = 0;
        for (const auto &result : optResults.value()){
            EXPECT_TRUE(i < mockSize);
            ereol::ChecklistItem mockResult = profileTH.checklistMockData.at(i);

            EXPECT_STREQ(mockResult.loanIdentifier.identifier.c_str(), result.loanIdentifier.identifier.c_str());
            EXPECT_STREQ(mockResult.loanIdentifier.isbn.c_str(), result.loanIdentifier.isbn.c_str());

            EXPECT_EQ(mockResult.creationDateUtc, result.creationDateUtc);
            i++;
        }
    }

}

TEST(ProfileTest, DISABLED_GetReservationsTest) {
    EXPECT_TRUE(profileTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(profileTH.optToken.value()));

    std::optional<std::vector<ereol::Reservation>> optResults = ereol::Profile::getReservations(profileTH.optToken.value());
    EXPECT_TRUE(optResults.has_value());
    if(optResults.has_value()){
        int mockSize = profileTH.reservationsMockData.size();
        int i = 0;
        for (const auto &result : optResults.value()){
            EXPECT_TRUE(i < mockSize);
            ereol::Reservation mockResult = profileTH.reservationsMockData.at(i);

            EXPECT_STREQ(mockResult.loanIdentifier.identifier.c_str(), result.loanIdentifier.identifier.c_str());
            EXPECT_STREQ(mockResult.loanIdentifier.isbn.c_str(), result.loanIdentifier.isbn.c_str());

            EXPECT_STREQ(mockResult.bookId.c_str(), result.bookId.c_str());
            EXPECT_STREQ(mockResult.status.c_str(), result.status.c_str());
            EXPECT_EQ(mockResult.createdUtc, result.createdUtc);
            EXPECT_EQ(mockResult.expectedRedeemDateUtc, result.expectedRedeemDateUtc);
            EXPECT_EQ(mockResult.expireUtc, result.expireUtc);
            i++;
        }
    }
}
TEST(ProfileTest, DISABLED_GetLoanHistoryTest) {
    EXPECT_TRUE(profileTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(profileTH.optToken.value()));

    std::optional<std::vector<ereol::LoanHistorical>> optResults = ereol::Profile::getLoanHistory(profileTH.optToken.value());
    EXPECT_TRUE(optResults.has_value());
    if(optResults.has_value()){
        int mockSize = profileTH.loanHistoryMockData.size();
        int i = 0;
        for (const auto &result : optResults.value()){
            EXPECT_TRUE(i < mockSize);
            ereol::LoanHistorical mockResult = profileTH.loanHistoryMockData.at(i);

            EXPECT_STREQ(mockResult.loanIdentifier.identifier.c_str(), result.loanIdentifier.identifier.c_str());
            EXPECT_STREQ(mockResult.loanIdentifier.isbn.c_str(), result.loanIdentifier.isbn.c_str());

            EXPECT_STREQ(mockResult.creator.c_str(), result.creator.c_str());
            EXPECT_STREQ(mockResult.loanId.c_str(), result.loanId.c_str());
            EXPECT_STREQ(mockResult.publicationDate.c_str(), result.publicationDate.c_str());
            EXPECT_STREQ(mockResult.title.c_str(), result.title.c_str());
            EXPECT_EQ(mockResult.loanDate, result.loanDate);
            EXPECT_EQ(mockResult.manuallyAdded, result.manuallyAdded);

            EXPECT_EQ(mockResult.materialTypes.size(), result.materialTypes.size());
            EXPECT_EQ(1, mockResult.materialTypes.size());
            EXPECT_STREQ(mockResult.materialTypes.at(0).c_str(), result.materialTypes.at(0).c_str());
            i++;
        }
    }

}