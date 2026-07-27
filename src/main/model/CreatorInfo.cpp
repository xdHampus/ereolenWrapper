#include "CreatorInfo.h"
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif


void ereol::from_json(const std::string  &s, ereol::CreatorInfo& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::CreatorInfo & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::CreatorInfo& x) {
        x.source = j.value("source", std::string{});
        x.creator = j.value("creator", std::string{});
        x.subTitle = j.value("subTitle", std::string{});
        x.url = j.value("url", std::string{});
    }

    void to_json(json & j, const ereol::CreatorInfo & x) {
        j = json::object();
        j["source"] = x.source;
        j["creator"] = x.creator;
        j["subTitle"] = x.subTitle;
        j["url"] = x.url;
    }

}

#ifdef COMPILE_LUA
void ereol::luaRegisterCreatorInfo(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::CreatorInfo>("CreatorInfo")
            .addConstructor <void (*) (void)> ()
            .addProperty("source", &ereol::CreatorInfo::source)
            .addProperty("creator", &ereol::CreatorInfo::creator)
            .addProperty("subTitle", &ereol::CreatorInfo::subTitle)
            .addProperty("url", &ereol::CreatorInfo::url)
            .addFunction("toJson", std::function <std::string (const ereol::CreatorInfo*)> (
                [] (const ereol::CreatorInfo* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif
