#include "LoanIdentifier.h"
#include "../util/JSONHelper.h"
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
