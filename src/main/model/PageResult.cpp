#include "PageResult.h"
#include <vector>
#include <cstdlib>
#include "../util/JSONHelper.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#include <LuaBridge/Vector.h>
#include <LuaBridge/Optional.h>
#endif

namespace ereol {
    struct Collection {
        int64_t size;
        std::vector<Record> records;
    };
    void from_json(const nlohmann::json & j, ereol::Collection& x) {
        x.size = j.at("size").get<int64_t>();
        x.records = j.at("records").get<std::vector<ereol::Record>>();
    }

    void to_json(nlohmann::json & j, const ereol::Collection & x) {
        j = nlohmann::json::object();
        j["size"] = x.size;
        j["records"] = x.records;
    }

}


void ereol::from_json(const std::string  &s, ereol::PageResult& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::PageResult & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::PageResult& x) {
        x.count = j.at("count").get<int64_t>();
        x.more = j.at("more").get<bool>();
        for (const auto &collection : j.at("collections").get<std::vector<ereol::Collection>>()) {
            x.data.push_back(collection.records);
        }
        x.facets = j.at("facets").get<std::vector<ereol::Facet>>();
    }

    void to_json(json & j, const ereol::PageResult & x) {
        j = json::object();
        j["count"] = x.count;
        j["more"] = x.more;
        std::vector<ereol::Collection> collections = {};
        for (const auto &records : x.data) {
            collections.push_back(ereol::Collection {
                static_cast<int64_t>(records.size()),
                records
            });
        }
        j["collections"] = collections;
        j["facets"] = x.facets;
    }


}


#ifdef COMPILE_LUA
void ereol::luaRegisterPageResult(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::PageResult>("PageResult")
            .addConstructor <void (*) (void)> ()
            .addProperty("data", &ereol::PageResult::data)
            .addProperty("count", &ereol::PageResult::count)
            .addProperty("more", &ereol::PageResult::more)
            .addProperty("facets", &ereol::PageResult::facets)
            .addFunction("toJson", std::function <std::string (const ereol::PageResult*)> (
                [] (const ereol::PageResult* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif
