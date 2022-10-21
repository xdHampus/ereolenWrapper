#include "LibraryProfile.h"
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#endif

void ereol::from_json(const std::string  &s, ereol::LibraryProfile& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::LibraryProfile & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json &j, ereol::LibraryProfile &x) {
        x.maxConcurrentLoansPerBorrower = j.at("maxConcurrentLoansPerBorrower").get<int>();
        x.maxConcurrentReservationsPerBorrower = j.at("maxConcurrentReservationsPerBorrower").get<int>();
        x.maxConcurrentAudioLoansPerBorrower = j.at("maxConcurrentAudioLoansPerBorrower").get<int>();
        x.maxConcurrentAudioReservationsPerBorrower = j.at("maxConcurrentAudioReservationsPerBorrower").get<int>();
    }
    void to_json(json &j, const ereol::LibraryProfile &x) {
        j = json::object();
        j["maxConcurrentLoansPerBorrower"] = x.maxConcurrentLoansPerBorrower;
        j["maxConcurrentReservationsPerBorrower"] = x.maxConcurrentReservationsPerBorrower;
        j["maxConcurrentAudioLoansPerBorrower"] = x.maxConcurrentAudioLoansPerBorrower;
        j["maxConcurrentAudioReservationsPerBorrower"] = x.maxConcurrentAudioReservationsPerBorrower;
    }
}

#ifdef COMPILE_LUA
void ereol::luaRegisterLibraryProfile(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::LibraryProfile>("LibraryProfile")
            .addConstructor <void (*) (void)> ()
            .addProperty("maxConcurrentLoansPerBorrower", &ereol::LibraryProfile::maxConcurrentLoansPerBorrower)
            .addProperty("maxConcurrentReservationsPerBorrower", &ereol::LibraryProfile::maxConcurrentReservationsPerBorrower)
            .addProperty("maxConcurrentAudioLoansPerBorrower", &ereol::LibraryProfile::maxConcurrentAudioLoansPerBorrower)
            .addProperty("maxConcurrentAudioReservationsPerBorrower", &ereol::LibraryProfile::maxConcurrentAudioReservationsPerBorrower)
            .addFunction("toJson", std::function <std::string (const ereol::LibraryProfile*)> (
                [] (const ereol::LibraryProfile* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif
