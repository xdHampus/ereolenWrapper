#include "Language.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif
#ifdef COMPILE_LUA
void ereol::luaRegisterLanguage(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginNamespace("Language")
            .addConstant("UNKNOWN", static_cast<int>(ereol::Language::UNKNOWN))
            .addConstant("DANISH", static_cast<int>(ereol::Language::DANISH))
            .addConstant("ENGLISH", static_cast<int>(ereol::Language::ENGLISH))
        .endNamespace()
    .endNamespace();
}
#endif