#include "Suggestion.h"
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif


void ereol::from_json(const std::string  &s, ereol::Suggestion& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Suggestion & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::Suggestion& x) {
        x.facet = j.value("facet", std::string{});
        x.translationKey = j.value("translationKey", std::string{});
        x.suggestion = j.value("suggestion", std::string{});
    }

    void to_json(json & j, const ereol::Suggestion & x) {
        j = json::object();
        j["facet"] = x.facet;
        j["translationKey"] = x.translationKey;
        j["suggestion"] = x.suggestion;
    }

}

#ifdef COMPILE_LUA
void ereol::luaRegisterSuggestion(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Suggestion>("Suggestion")
            .addConstructor <void (*) (void)> ()
            .addProperty("facet", &ereol::Suggestion::facet)
            .addProperty("translationKey", &ereol::Suggestion::translationKey)
            .addProperty("suggestion", &ereol::Suggestion::suggestion)
            .addFunction("toJson", std::function <std::string (const ereol::Suggestion*)> (
                [] (const ereol::Suggestion* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif
