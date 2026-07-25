#include "Profile.h"
#include "util/JSONHelper.h"
#include "src/main/util/ApiCaller.h"
#ifdef COMPILE_LUA
#include "lua/LuaInterface.h"
// Every Profile method returns a Response<std::vector<...>>. Without these
// Stack<> specializations LuaBridge falls back to the userdata path and fails
// at runtime with "The class is not registered in LuaBridge".
#include <LuaBridge/Vector.h>
#include <LuaBridge/Optional.h>
#include <LuaBridge/Map.h>
#include "lua/ResponseLua.h"
#endif

const std::string libraryProfileMethod = "ereolen.getLibraryProfile";
const std::string loansMethod = "getLoans";
const std::string checklistMethod = "ereolen.getCheckList";
const std::string reservationsMethod = "getReservations";
const std::string loanHistoryMethod = "getLoanHistory";
const std::string addToCheckListMethod = "ereolen.addToCheckList";
const std::string removeFromCheckListMethod = "ereolen.removeFromCheckList";
const std::string addReservationMethod = "addReservation";
const std::string removeReservationsMethod = "removeReservations";

ereol::Response<ereol::LibraryProfile> ereol::Profile::getLibraryProfile(ereol::Library library) {
    std::string payload = ereol::ApiCaller::defaultPayloadJSON(libraryProfileMethod, library);
    return ereol::ApiCaller::getResponse<ereol::LibraryProfile>(payload);
}

ereol::Response<std::vector<ereol::LoanActive>> ereol::Profile::getLoans(ereol::Token token) {
    std::string payload = ereol::ApiCaller::defaultPayloadJSON(loansMethod, token.library);
    return ereol::ApiCaller::getResponse<std::vector<ereol::LoanActive>>(payload, token);
}

ereol::Response<std::vector<ereol::ChecklistItem>> ereol::Profile::getCheckList(ereol::Token token) {
    std::string payload = ereol::ApiCaller::defaultPayloadJSON(checklistMethod, token.library);
    return ereol::ApiCaller::getResponse<std::vector<ereol::ChecklistItem>>(payload, token);
}

ereol::Response<std::vector<ereol::Reservation>> ereol::Profile::getReservations(ereol::Token token) {
    std::string payload = ereol::ApiCaller::defaultPayloadJSON(reservationsMethod, token.library);
    return ereol::ApiCaller::getResponse<std::vector<ereol::Reservation>>(payload, token);
}

ereol::Response<std::vector<ereol::LoanHistorical>> ereol::Profile::getLoanHistory(ereol::Token token) {
    std::string payload = ereol::ApiCaller::defaultPayloadJSON(loanHistoryMethod, token.library);
    return ereol::ApiCaller::getResponse<std::vector<ereol::LoanHistorical>>(payload, token);
}

ereol::Response<bool> ereol::Profile::addToCheckList(std::string identifier, ereol::Token token) {
    std::string payload = ereol::ApiCaller::defaultPayloadIdentifierJSON(addToCheckListMethod, identifier, token.library);
    return ereol::ApiCaller::getAck(payload, token);
}

ereol::Response<bool> ereol::Profile::removeFromCheckList(std::vector<std::string> identifiers, ereol::Token token) {
    std::string payload = ereol::ApiCaller::defaultPayloadIdentifiersJSON(removeFromCheckListMethod, identifiers, token.library);
    return ereol::ApiCaller::getAck(payload, token);
}

ereol::Response<bool> ereol::Profile::addReservation(std::string identifier, std::string email, std::string phone, ereol::Token token) {
    // 7 params: prefix, identifier, email, phone. The app requires the user to
    // have an email and phone on file before offering to reserve.
    std::string payload = ereol::ApiEnv::getRpcPayloadJSON(
            addReservationMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    identifier,
                    email,
                    phone
            });
    return ereol::ApiCaller::getAck(payload, token);
}

ereol::Response<bool> ereol::Profile::removeReservations(std::vector<std::string> identifiers, ereol::Token token) {
    std::string payload = ereol::ApiCaller::defaultPayloadIdentifiersJSON(removeReservationsMethod, identifiers, token.library);
    return ereol::ApiCaller::getAck(payload, token);
}

#ifdef COMPILE_LUA
void ereol::luaRegisterProfile(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Profile>("Profile")
            .addStaticFunction ("getLibraryProfile",
                std::function<ereol::Response<ereol::LibraryProfile>(int)>(
                [](int library){
                    return ereol::Profile::getLibraryProfile(static_cast<ereol::Library>(library));
                })
            )
            .addStaticFunction ("getLoans", ereol::Profile::getLoans)
            .addStaticFunction ("getCheckList", ereol::Profile::getCheckList)
            .addStaticFunction ("getReservations", ereol::Profile::getReservations)
            .addStaticFunction ("getLoanHistory", ereol::Profile::getLoanHistory)
            .addStaticFunction ("addToCheckList", ereol::Profile::addToCheckList)
            .addStaticFunction ("removeFromCheckList", ereol::Profile::removeFromCheckList)
            .addStaticFunction ("addReservation", ereol::Profile::addReservation)
            .addStaticFunction ("removeReservations", ereol::Profile::removeReservations)
        .endClass()
    .endNamespace();
}
#endif