//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_PROFILE_H
#define EREOLENWRAPPER_PROFILE_H

#include "ApiEnv.h"
#include "structs/LibraryProfile.h"
#include "structs/LoanActive.h"
#include "structs/Token.h"
#include "structs/ChecklistItem.h"
#include "structs/LoanHistorical.h"
#include "src/main/structs/Reservation.h"
#ifdef __cplusplus 
#include <string>
#include <optional>
#include <vector>
namespace ereol {
    class Profile {
    private:
        static const std::string libraryProfileMethod;
        static const std::string loansMethod;
        static const std::string checklistMethod;
        static const std::string reservationsMethod;
        static const std::string loanHistoryMethod;
    public:
        static std::optional<ereol::LibraryProfile> getLibraryProfile(ereol::Library library);
        static std::optional<std::vector<ereol::LoanActive>> getLoans(ereol::Token token);
        static std::optional<std::vector<ereol::ChecklistItem>> getCheckList(ereol::Token token);
        static std::optional<std::vector<ereol::Reservation>> getReservations(ereol::Token token);
        static std::optional<std::vector<ereol::LoanHistorical>> getLoanHistory(ereol::Token token);
    };
#else
LibraryProfile*  ereol_Profile_getLibraryProfile(Library* library); 
LoanActive*  ereol_Profile_getLoans(Token* token); 
ChecklistItem* ereol_Profile_getChecklist(Token* token); 
Reservation*  ereol_Profile_getReservations(Token* token); 
LoanHistorical*  ereol_Profile_getLoanHistory(Token* token); 
#endif
#ifdef __cplusplus 
}
#endif


#endif //EREOLENWRAPPER_PROFILE_H
