#include "Token.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif

#ifdef COMPILE_LUA
void ereol::luaRegisterToken(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Token>("Token")
            .addConstructor <void (*) (void)> ()
            .addProperty("timeFetched", &ereol::Token::timeFetched)
            .addProperty("sessid", &ereol::Token::sessid)
            .addProperty("expirationDate", &ereol::Token::expirationDate)
            .addProperty("library",
                std::function<int(const ereol::Token*)>([](const ereol::Token* o) { return static_cast<int>(o->library);}),
                std::function<void(ereol::Token*, int)>([](ereol::Token* o, int x) { o->library = static_cast<ereol::Library>(x);})
             )
        .endClass()
    .endNamespace();
}
#endif