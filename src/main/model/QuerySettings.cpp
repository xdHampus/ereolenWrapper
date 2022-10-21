#include "QuerySettings.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#include <LuaBridge/Map.h>
#include <LuaBridge/Optional.h>
#endif

#ifdef COMPILE_LUA
void ereol::luaRegisterQuerySettings(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::QuerySettings>("QuerySettings")
            .addConstructor <void (*) (void)> ()
            .addProperty("startIndex", &ereol::QuerySettings::startIndex)
            .addProperty("endIndex", &ereol::QuerySettings::endIndex)
            .addProperty("facets", &ereol::QuerySettings::facets)
        .endClass()
    .endNamespace();
}
#endif