#include "LoanIdentifier.h"
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif
void ereol::from_json(const std::string  &s, ereol::LoanIdentifier& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::LoanIdentifier & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::LoanIdentifier& x) {
        x.identifier = j.at("identifier").get<std::string>();
        x.isbn = j.at("isbn").get<std::string>();
    }
    void to_json(json & j, const ereol::LoanIdentifier & x) {
        j = json::object();
        j["identifier"] = x.identifier;
        j["isbn"] = x.isbn;
    }
}


#ifdef COMPILE_LUA
void ereol::luaRegisterLoanIdentifier(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::LoanIdentifier>("LoanIdentifier")
            .addConstructor <void (*) (void)> ()
            .addProperty("identifier", &ereol::LoanIdentifier::identifier)
            .addProperty("isbn", &ereol::LoanIdentifier::isbn)
            .addFunction("toJson", std::function <std::string (const ereol::LoanIdentifier*)> (
                [] (const ereol::LoanIdentifier* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif