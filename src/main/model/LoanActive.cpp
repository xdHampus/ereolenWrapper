#include "LoanActive.h"
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif

void ereol::from_json(const std::string  &s, ereol::LoanActive& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::LoanActive & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::LoanActive& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();
        x.retailerOrderNumber = j.at("retailerOrderNumber").get<std::string>();
        x.internalOrderNumber = j.at("internalOrderNumber").get<std::string>();
        x.orderDate = j.at("orderDate").get<int64_t>();
        x.expireDate = j.at("expireDate").get<int64_t>();
        x.downloadUrl = j.at("downloadUrl").get<std::string>();
        x.isSubscription = j.at("isSubscription").get<bool>();
    }

    void to_json(json & j, const ereol::LoanActive & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;
        j["retailerOrderNumber"] = x.retailerOrderNumber;
        j["internalOrderNumber"] = x.internalOrderNumber;
        j["orderDate"] = x.orderDate;
        j["expireDate"] = x.expireDate;
        j["downloadUrl"] = x.downloadUrl;
        j["isSubscription"] = x.isSubscription;
    }
}

#ifdef COMPILE_LUA
void ereol::luaRegisterLoanActive(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::LoanActive>("LoanActive")
            .addConstructor <void (*) (void)> ()
            .addProperty("loanIdentifier", &ereol::LoanActive::loanIdentifier)
            .addProperty("retailerOrderNumber", &ereol::LoanActive::retailerOrderNumber)
            .addProperty("internalOrderNumber", &ereol::LoanActive::internalOrderNumber)
            .addProperty("orderDate", &ereol::LoanActive::orderDate)
            .addProperty("expireDate", &ereol::LoanActive::expireDate)
            .addProperty("downloadUrl", &ereol::LoanActive::downloadUrl)
            .addProperty("isSubscription", &ereol::LoanActive::isSubscription)
            .addFunction("toJson", std::function <std::string (const ereol::LoanActive*)> (
                [] (const ereol::LoanActive* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif