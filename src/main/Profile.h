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
    };
}
#endif //EREOLENWRAPPER_PROFILE_H
