#include "Facet.h"
#include "../util/InterfaceUtilC.h"
#ifdef __cplusplus
#include <functional>
#include <vector>

#include <cstring>
#include <cstdlib>
#include "../util/JSONHelper.h"



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

extern "C" {
namespace ereol {
#endif

#ifdef __cplusplus
};
}
#endif  // __cplusplus 