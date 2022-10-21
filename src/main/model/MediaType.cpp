#include "MediaType.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif
#ifdef COMPILE_LUA
void ereol::luaRegisterMediaType(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginNamespace("MediaType")
            .addConstant("AUDIO", static_cast<int>(ereol::MediaType::AUDIO))
            .addConstant("TEXT", static_cast<int>(ereol::MediaType::TEXT))
        .endNamespace()
    .endNamespace();
}
#endif
