//
// Created by root on 1/30/22.
//

#include "Profile.h"
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
    return {};
}

std::optional<std::vector<ereol::ChecklistItem>> ereol::Profile::getCheckList(ereol::Token token) {
    return {};
}

std::optional<std::vector<ereol::Reservation>> ereol::Profile::getReservations(ereol::Token token) {
    return {};
}

std::optional<std::vector<ereol::LoanHistorical>> ereol::Profile::getLoanHistory(ereol::Token token) {
    return {};
}
