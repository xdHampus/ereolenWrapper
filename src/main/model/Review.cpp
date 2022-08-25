#include "Review.h"
#include "../util/InterfaceUtilC.h"
#ifdef __cplusplus
#include <functional>
#include <vector>

#include <cstring>
#include <cstdlib>
#include "../util/JSONHelper.h"



void ereol::from_json(const std::string  &s, ereol::Review& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Review & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::Review& x) {
        x.url = j.at("url").get<std::string>();
        x.source = j.at("source").get<std::string>();
        x.subTitle = j.at("subTitle").get<std::string>();
    }

    void to_json(json & j, const ereol::Review & x) {
        j = json::object();
        j["url"] = x.url;
        j["source"] = x.source;
        j["subTitle"] = x.subTitle;
    }

}

extern "C" {
namespace ereol {
#endif

#ifdef __cplusplus
};
}
#endif  // __cplusplus 