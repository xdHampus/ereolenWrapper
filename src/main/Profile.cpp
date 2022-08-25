#include "Profile.h"
#include <cpr/cpr.h>
#include "util/JSONHelper.h"

const std::string libraryProfileMethod = "ereolen.getLibraryProfile";
const std::string loansMethod = "getLoans";
const std::string checklistMethod = "ereolen.getCheckList";
const std::string reservationsMethod = "getReservations";
const std::string loanHistoryMethod = "getLoanHistory";

std::optional<ereol::LibraryProfile> ereol::Profile::getLibraryProfile(ereol::Library library) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            libraryProfileMethod,
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
            loansMethod,
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
                    results.push_back(item.value().get<ereol::LoanActive>());
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
            checklistMethod,
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
                    results.push_back(item.value().get<ereol::ChecklistItem>());
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
            reservationsMethod,
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
                    results.push_back(item.value().get<ereol::Reservation>());
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
            loanHistoryMethod,
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
                    results.push_back(item.value().get<ereol::LoanHistorical>());                    
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