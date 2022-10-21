#include "Facet.h"
#include <vector>
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#include <LuaBridge/Vector.h>
#endif


void ereol::from_json(const std::string  &s, ereol::Facet& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Facet & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::Facet& x) {
        x.name = j.at("name").get<std::string>();
        x.terms = j.at("terms").get<std::vector<ereol::Term>>();
        x.type = j.at("type").get<std::string>();
        x.translationKey = j.at("translationKey").get<std::string>();
    }

    void to_json(json & j, const ereol::Facet & x) {
        j = json::object();
        j["name"] = x.name;
        j["terms"] = x.terms;
        j["type"] = x.type;
        j["translationKey"] = x.translationKey;
    }

}

#ifdef COMPILE_LUA
void ereol::luaRegisterFacet(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Facet>("Facet")
            .addConstructor <void (*) (void)> ()
            .addProperty("name", &ereol::Facet::name)
            .addProperty("terms", &ereol::Facet::terms)
            .addProperty("type", &ereol::Facet::type)
            .addProperty("translationKey", &ereol::Facet::translationKey)
            .addFunction("toJson", std::function <std::string (const ereol::Facet*)> (
                [] (const ereol::Facet* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif