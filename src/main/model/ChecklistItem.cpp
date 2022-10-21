#include "ChecklistItem.h"
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif

void ereol::from_json(const std::string  &s, ereol::ChecklistItem& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::ChecklistItem & x){
    nlohmann::json j = x;
    s = j.dump();
}


namespace nlohmann {
    void from_json(const json & j, ereol::ChecklistItem& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();
        x.creationDateUtc = j.at("creationDateUtc").get<int64_t>();
    }

    void to_json(json & j, const ereol::ChecklistItem & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;
        j["creationDateUtc"] = x.creationDateUtc;
    }
}

#ifdef COMPILE_LUA
void ereol::luaRegisterChecklistItem(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::ChecklistItem>("ChecklistItem")
            .addConstructor <void (*) (void)> ()
            .addProperty("loanIdentifier", &ereol::ChecklistItem::loanIdentifier)
            .addProperty("creationDateUtc", &ereol::ChecklistItem::creationDateUtc)
            .addFunction("toJson", std::function <std::string (const ereol::ChecklistItem*)> (
                [] (const ereol::ChecklistItem* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif