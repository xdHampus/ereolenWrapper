#include "LuaInterface.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <lua.h>
#include <lauxlib.h>
using namespace luabridge;

#ifdef __cplusplus
extern "C" {
namespace ereol {
#endif

int luaopen_libereolenwrapper(lua_State *L) {
    //model
    ereol::luaRegisterChecklistItem(L);
    ereol::luaRegisterContributor(L);
    ereol::luaRegisterFacet(L);
    ereol::luaRegisterLanguage(L);
    ereol::luaRegisterLibrary(L);
    ereol::luaRegisterLibraryProfile(L);
    ereol::luaRegisterLoanActive(L);
    ereol::luaRegisterLoanHistorical(L);
    ereol::luaRegisterLoanIdentifier(L);
    ereol::luaRegisterMediaType(L);
    ereol::luaRegisterPageResult(L);
    ereol::luaRegisterQuerySettings(L);
    ereol::luaRegisterRecord(L);
    ereol::luaRegisterRecordType(L);
    ereol::luaRegisterReservation(L);
    ereol::luaRegisterResponse(L);
    ereol::luaRegisterReview(L);
    ereol::luaRegisterRpcPayload(L);
    ereol::luaRegisterTerm(L);
    ereol::luaRegisterToken(L);
    //api
    ereol::luaRegisterAuth(L);
    ereol::luaRegisterProfile(L);
    ereol::luaRegisterItem(L);
    ereol::luaRegisterApiEnv(L);

    return 1;
}

#ifdef __cplusplus
}}
#endif
