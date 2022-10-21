#include "RecordType.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif



#ifdef COMPILE_LUA
void ereol::luaRegisterRecordType(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginNamespace("RecordType")
            .addConstant("AUDIOBOOK", static_cast<int>(ereol::RecordType::AUDIOBOOK))
            .addConstant("EBOOK", static_cast<int>(ereol::RecordType::EBOOK))
            .addConstant("PODCAST", static_cast<int>(ereol::RecordType::PODCAST))
        .endNamespace()
    .endNamespace();
}
#endif