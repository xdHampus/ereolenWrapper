//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_PROFILE_H
#define EREOLENWRAPPER_PROFILE_H

#include "ApiEnv.h"
#include "model/LibraryProfile.h"
#include "model/LoanActive.h"
#include "model/Token.h"
#include "model/ChecklistItem.h"
#include "model/LoanHistorical.h"
#include "src/main/model/Reservation.h"
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
#include "util/InterfaceUtilC.h"
LibraryProfile*  ereol_Profile_getLibraryProfile(Library* library); 
VectorVoid* ereol_Profile_getLoans(Token* token); 
VectorVoid* ereol_Profile_getChecklist(Token* token); 
VectorVoid* ereol_Profile_getReservations(Token* token); 
VectorVoid* ereol_Profile_getLoanHistory(Token* token); 
#endif
#ifdef __cplusplus 
}
#endif


#endif //EREOLENWRAPPER_PROFILE_H
