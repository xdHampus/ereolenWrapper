#include "Contributor.h"
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::Contributor& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Contributor & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::Contributor& x) {
        x.type = j.at("type").get<std::string>();
        x.composedName = j.at("composedName").get<std::string>();
        x.firstName = j.at("firstName").get<std::string>();
        x.lastName = j.at("lastName").get<std::string>();
    }
    void to_json(json & j, const ereol::Contributor & x) {
        j = json::object();
        j["type"] = x.type;
        j["composedName"] = x.composedName;
        j["firstName"] = x.firstName;
        j["lastName"] = x.lastName;
    }
}














