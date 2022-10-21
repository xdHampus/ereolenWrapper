#ifndef EREOLENWRAPPER_LUAINTERFACE_H
#define EREOLENWRAPPER_LUAINTERFACE_H
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>


using namespace luabridge;

#ifdef __cplusplus
extern "C" {
namespace ereol {
#endif

    int luaopen_libereolenwrapper(lua_State *L);

    //model/* registrations
    void luaRegisterChecklistItem(lua_State *L);

    void luaRegisterContributor(lua_State *L);

    void luaRegisterFacet(lua_State *L);

    void luaRegisterLanguage(lua_State *L);

    void luaRegisterLibrary(lua_State *L);

    void luaRegisterLibraryProfile(lua_State *L);

    void luaRegisterLoanActive(lua_State *L);

    void luaRegisterLoanHistorical(lua_State *L);

    void luaRegisterLoanIdentifier(lua_State *L);

    void luaRegisterMediaType(lua_State *L);

    void luaRegisterPageResult(lua_State *L);

    void luaRegisterQuerySettings(lua_State *L);

    void luaRegisterRecord(lua_State *L);

    void luaRegisterRecordType(lua_State *L);

    void luaRegisterReservation(lua_State *L);

    void luaRegisterResponse(lua_State *L);

    void luaRegisterReview(lua_State *L);

    void luaRegisterRpcPayload(lua_State *L);

    void luaRegisterTerm(lua_State *L);

    void luaRegisterToken(lua_State *L);


    //api interface registrations;
    void luaRegisterAuth(lua_State *L);

    void luaRegisterProfile(lua_State *L);

    void luaRegisterItem(lua_State *L);

    void luaRegisterApiEnv(lua_State *L);


#ifdef __cplusplus
}
}
#endif





#endif //EREOLENWRAPPER_LUAINTERFACE_H
