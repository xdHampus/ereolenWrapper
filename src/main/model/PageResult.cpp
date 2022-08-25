#include "PageResult.h"
#include "../util/InterfaceUtilC.h"
#ifdef __cplusplus
#include <functional>
#include <vector>

#include <cstring>
#include <cstdlib>
#include "../util/JSONHelper.h"

namespace ereol {
    struct Collection {
        int64_t size;
        std::vector<Record> records;
    };
    inline void from_json(const nlohmann::json & j, ereol::Collection& x) {
        x.size = j.at("size").get<int64_t>();
        x.records = j.at("records").get<std::vector<ereol::Record>>();
    }

    inline void to_json(nlohmann::json & j, const ereol::Collection & x) {
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

extern "C" {
namespace ereol {
#endif
    
#ifdef __cplusplus
};
}
#endif  // __cplusplus 