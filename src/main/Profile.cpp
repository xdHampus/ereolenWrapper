#include "Profile.h"
#include "util/JSONHelper.h"
#include "src/main/util/ApiCaller.h"
#ifdef COMPILE_LUA
#include "lua/LuaInterface.h"
#include "lua/ResponseLua.h"
#endif

const std::string libraryProfileMethod = "ereolen.getLibraryProfile";
const std::string loansMethod = "getLoans";
const std::string checklistMethod = "ereolen.getCheckList";
const std::string reservationsMethod = "getReservations";
const std::string loanHistoryMethod = "getLoanHistory";

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
        .endClass()
    .endNamespace();
}
#endif