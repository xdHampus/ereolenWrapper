//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_PROFILE_H
#define EREOLENWRAPPER_PROFILE_H

#include <string>
#include <optional>
#include <vector>

#include "ApiEnv.h"
#include "structs/LibraryProfile.h"
#include "structs/LoanActive.h"
#include "structs/Token.h"
#include "structs/ChecklistItem.h"
#include "structs/LoanHistorical.h"
#include "src/main/structs/Reservation.h"


namespace ereol {
    class Profile {
    private:
        inline static const std::string libraryProfileMethod = "ereolen.getLibraryProfile";
        inline static const std::string loansMethod = "getLoans";
        inline static const std::string checklistMethod = "ereolen.getCheckList";
        inline static const std::string reservationsMethod = "getReservations";
        inline static const std::string loanHistoryMethod = "getLoanHistory";
    public:
        static std::optional<ereol::LibraryProfile> getLibraryProfile(ereol::Library library);
        static std::optional<std::vector<ereol::LoanActive>> getLoans(ereol::Token token);
        static std::optional<std::vector<ereol::ChecklistItem>> getCheckList(ereol::Token token);
        static std::optional<std::vector<ereol::Reservation>> getReservations(ereol::Token token);
        static std::optional<std::vector<ereol::LoanHistorical>> getLoanHistory(ereol::Token token);

    };
}



#endif //EREOLENWRAPPER_PROFILE_H
