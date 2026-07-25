#ifndef EREOLENWRAPPER_PROFILE_H
#define EREOLENWRAPPER_PROFILE_H
#include "ApiEnv.h"
#include "model/LibraryProfile.h"
#include "model/LoanActive.h"
#include "model/Token.h"
#include "model/ChecklistItem.h"
#include "model/LoanHistorical.h"
#include "model/Reservation.h"
#include "model/Response.h"
#include <vector>
#include <string>
namespace ereol {
    class Profile {
    public:
        static ereol::Response<ereol::LibraryProfile> getLibraryProfile(ereol::Library library);
        static ereol::Response<std::vector<ereol::LoanActive>> getLoans(ereol::Token token);
        static ereol::Response<std::vector<ereol::ChecklistItem>> getCheckList(ereol::Token token);
        static ereol::Response<std::vector<ereol::Reservation>> getReservations(ereol::Token token);
        static ereol::Response<std::vector<ereol::LoanHistorical>> getLoanHistory(ereol::Token token);

        // Write side. Arities confirmed against the server 2026-07-25:
        // addToCheckList/removeFromCheckList/removeReservations take 5 params,
        // addReservation 7 to 8 (the 8th is optional and unused by the app).
        static ereol::Response<bool> addToCheckList(std::string identifier, ereol::Token token);
        static ereol::Response<bool> removeFromCheckList(std::vector<std::string> identifiers, ereol::Token token);
        static ereol::Response<bool> addReservation(std::string identifier, std::string email, std::string phone, ereol::Token token);
        static ereol::Response<bool> removeReservations(std::vector<std::string> identifiers, ereol::Token token);
    };
}
#endif //EREOLENWRAPPER_PROFILE_H
