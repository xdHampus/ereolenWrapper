//
// Created by root on 1/30/22.
//

#include "Profile.h"
#ifdef __cplusplus 
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

std::optional<ereol::LibraryProfile> ereol::Profile::getLibraryProfile(ereol::Library library) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            ereol::Profile::libraryProfileMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(library),
            }
    );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}});

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                ereol::LibraryProfile profile = ereol::LibraryProfile();

                profile.maxConcurrentLoansPerBorrower =
                        jr["result"]["data"]["maxConcurrentLoansPerBorrower"].get<int>();
                profile.maxConcurrentReservationsPerBorrower =
                        jr["result"]["data"]["maxConcurrentReservationsPerBorrower"].get<int>();
                profile.maxConcurrentAudioLoansPerBorrower =
                        jr["result"]["data"]["maxConcurrentAudioLoansPerBorrower"].get<int>();
                profile.maxConcurrentAudioReservationsPerBorrower =
                        jr["result"]["data"]["maxConcurrentAudioReservationsPerBorrower"].get<int>();

                return {profile};
            } else { //TODO: Invalid input or no result
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return {};
}

std::optional<std::vector<ereol::LoanActive>> ereol::Profile::getLoans(ereol::Token token) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            ereol::Profile::loansMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library)
            }
    );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});


    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                std::vector<ereol::LoanActive> results = {};

                for (const auto& item : jr["result"]["data"].items())
                {
                    ereol::LoanActive result = {
                            ereol::LoanIdentifier{
                                    item.value()["identifier"].get<std::string>(),
                                    item.value()["isbn"].get<std::string>()
                            },
                            item.value()["retailerOrderNumber"].get<std::string>(),
                            item.value()["internalOrderNumber"].get<std::string>(),
                            item.value()["orderDate"].get<int>(),
                            item.value()["expireDate"].get<int>(),
                            item.value()["downloadUrl"].get<std::string>(),
                            item.value()["isSubscription"].get<bool>()
                    };
                    results.push_back(result);
                }

                return {results};
            } else { //TODO: Invalid input or no result
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return {};
}

std::optional<std::vector<ereol::ChecklistItem>> ereol::Profile::getCheckList(ereol::Token token) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            ereol::Profile::checklistMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library)
            }
    );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});


    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                std::vector<ereol::ChecklistItem> results = {};

                for (const auto& item : jr["result"]["data"].items())
                {
                    ereol::ChecklistItem result = {
                            ereol::LoanIdentifier{
                                    item.value()["identifier"].get<std::string>(),
                                    item.value()["isbn"].get<std::string>()
                            },
                            item.value()["creationDateUtc"].get<int>()
                    };
                    results.push_back(result);
                }

                return {results};
            } else { //TODO: Invalid input or no result
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return {};
}

std::optional<std::vector<ereol::Reservation>> ereol::Profile::getReservations(ereol::Token token) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            ereol::Profile::reservationsMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library)
            }
    );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});


    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                std::vector<ereol::Reservation> results = {};

                for (const auto& item : jr["result"]["data"].items())
                {
                    ereol::Reservation result = {
                            ereol::LoanIdentifier{
                                    item.value()["identifier"].get<std::string>(),
                                    item.value()["isbn"].get<std::string>()
                            },
                            item.value()["bookid"].get<std::string>(),
                            item.value()["status"].get<std::string>(),
                            item.value()["createdUtc"].get<int>(),
                            item.value()["expireUtc"].get<int>(),
                            item.value()["expectedRedeemDateUtc"].get<int>()
                    };
                    results.push_back(result);
                }
                return {results};
            } else { //TODO: Invalid input or no result
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return {};
}

std::optional<std::vector<ereol::LoanHistorical>> ereol::Profile::getLoanHistory(ereol::Token token) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            ereol::Profile::loanHistoryMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library)
            }
    );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});


    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);

        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                std::vector<ereol::LoanHistorical> results = {};

                for (const auto& item : jr["result"]["data"].items())
                {
                    ereol::LoanHistorical result = {
                            ereol::LoanIdentifier{
                                    item.value()["identifier"].get<std::string>(),
                                    item.value()["isbn"].get<std::string>()
                            },
                            item.value()["loanId"].get<std::string>(),
                            item.value()["loanDate"].get<int>(),
                            item.value()["manuallyAdded"].get<bool>(),
                            item.value()["title"].get<std::string>(),
                            item.value()["creator"].get<std::string>(),
                            item.value()["publicationDate"].get<std::string>(),
                            item.value()["materialTypes"].get<std::vector<std::string>>()
                    };
                    
                    results.push_back(result);
                }

                return {results};
            } else { //TODO: Invalid input or no result
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return {};
}

extern "C" { 
    namespace ereol {
#endif
        LibraryProfile*  ereol_Profile_getLibraryProfile(Library* library) {
            std::optional<LibraryProfile> optLibraryProfile = ereol::Profile::getLibraryProfile(*library);
            if(optLibraryProfile.has_value()){
                return &optLibraryProfile.value();
            } else {
                return nullptr;
            }
        }
        LoanActive*  ereol_Profile_getLoans(Token* token) {
            std::optional<std::vector<LoanActive>> optLoans = ereol::Profile::getLoans(*token);
            if(optLoans.has_value()){
                return optLoans.value().data();
            } else {
                return nullptr;
            }
        }
        ChecklistItem*  ereol_Profile_getChecklist(Token* token) {
            std::optional<std::vector<ChecklistItem>> optChecklist = ereol::Profile::getCheckList(*token);
            if(optChecklist.has_value()){
                return optChecklist.value().data();
            } else {
                return nullptr;
            }
        }        
        Reservation*  ereol_Profile_getReservations(Token* token) {
            std::optional<std::vector<Reservation>> optReservations = ereol::Profile::getReservations(*token);
            if(optReservations.has_value()){
                return optReservations.value().data();
            } else {
                return nullptr;
            }
        }
        LoanHistorical*  ereol_Profile_getLoanHistory(Token* token) {
            std::optional<std::vector<LoanHistorical>> optLoanHistory = ereol::Profile::getLoanHistory(*token);
            if(optLoanHistory.has_value()){
                return optLoanHistory.value().data();
            } else {
                return nullptr;
            }
        }                

#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 