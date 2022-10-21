#include "Term.h"
#include <cstdlib>
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif


void ereol::from_json(const std::string  &s, ereol::Term& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Term & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::Term& x) {
        x.term = j.at("term").get<std::string>();
        x.value = j.at("value").get<std::string>();
        x.quantity = j.at("quantity").get<int64_t>();
    }

    void to_json(json & j, const ereol::Term & x) {
        j = json::object();
        j["term"] = x.term;
        j["value"] = x.value;
        j["quantity"] = x.quantity;
    }

}

#ifdef COMPILE_LUA
void ereol::luaRegisterTerm(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Term>("Term")
            .addConstructor <void (*) (void)> ()
            .addProperty("term", &ereol::Term::term)
            .addProperty("value", &ereol::Term::value)
            .addProperty("quantity", &ereol::Term::quantity)
            .addFunction("toJson", std::function <std::string (const ereol::Term*)> (
                [] (const ereol::Term* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif