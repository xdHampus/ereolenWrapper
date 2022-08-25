#include "Term.h"
#include <cstdlib>
#include "../util/JSONHelper.h"

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
