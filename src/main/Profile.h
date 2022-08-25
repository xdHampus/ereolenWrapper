#ifndef EREOLENWRAPPER_PROFILE_H
#define EREOLENWRAPPER_PROFILE_H
#include "ApiEnv.h"
#include "model/LibraryProfile.h"
#include "model/LoanActive.h"
#include "model/Token.h"
#include "model/ChecklistItem.h"
#include "model/LoanHistorical.h"
#include "src/main/model/Reservation.h"
#include <string>
#include <optional>
#include <vector>
namespace ereol {
    class Profile {
    public:
        static std::optional<ereol::LibraryProfile> getLibraryProfile(ereol::Library library);
        static std::optional<std::vector<ereol::LoanActive>> getLoans(ereol::Token token);
        static std::optional<std::vector<ereol::ChecklistItem>> getCheckList(ereol::Token token);
        static std::optional<std::vector<ereol::Reservation>> getReservations(ereol::Token token);
        static std::optional<std::vector<ereol::LoanHistorical>> getLoanHistory(ereol::Token token);
    };
}
#endif //EREOLENWRAPPER_PROFILE_H
