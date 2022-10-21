#include "Review.h"
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif


void ereol::from_json(const std::string  &s, ereol::Review& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Review & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::Review& x) {
        x.url = j.at("url").get<std::string>();
        x.source = j.at("source").get<std::string>();
        x.subTitle = j.at("subTitle").get<std::string>();
    }

    void to_json(json & j, const ereol::Review & x) {
        j = json::object();
        j["url"] = x.url;
        j["source"] = x.source;
        j["subTitle"] = x.subTitle;
    }

}

#ifdef COMPILE_LUA
void ereol::luaRegisterReview(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Review>("Review")
            .addConstructor <void (*) (void)> ()
            .addProperty("source", &ereol::Review::source)
            .addProperty("subTitle", &ereol::Review::subTitle)
            .addProperty("url", &ereol::Review::url)
            .addFunction("toJson", std::function <std::string (const ereol::Review*)> (
                [] (const ereol::Review* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif