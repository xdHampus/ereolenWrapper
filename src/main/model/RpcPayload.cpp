#include "RpcPayload.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#include <LuaBridge/Vector.h>
#endif

#ifdef COMPILE_LUA
void ereol::luaRegisterRpcPayload(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::RpcPayload>("RpcPayload")
            .addConstructor <void (*) (void)> ()
            .addProperty("jsonrpc", &ereol::RpcPayload::jsonrpc)
            .addProperty("method", &ereol::RpcPayload::method)
            .addProperty("params", &ereol::RpcPayload::params)
            .addProperty("id", &ereol::RpcPayload::id)
        .endClass()
    .endNamespace();
}
#endif