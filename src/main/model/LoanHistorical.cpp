#include "LoanHistorical.h"
#include <functional>
#include <cstdlib>
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::LoanHistorical& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::LoanHistorical & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::LoanHistorical& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();
        x.loanId = j.at("loanId").get<std::string>();
        x.loanDate = j.at("loanDate").get<int64_t>();
        x.manuallyAdded = j.at("manuallyAdded").get<bool>();
        x.title = j.at("title").get<std::string>();
        x.creator = j.at("creator").get<std::string>();
        x.publicationDate = j.at("publicationDate").get<std::string>();
        x.materialTypes = j.at("materialTypes").get<std::vector<std::string>>();
    }

    void to_json(json & j, const ereol::LoanHistorical & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;
        j["loanId"] = x.loanId;
        j["loanDate"] = x.loanDate;
        j["manuallyAdded"] = x.manuallyAdded;
        j["title"] = x.title;
        j["creator"] = x.creator;
        j["publicationDate"] = x.publicationDate;
        j["materialTypes"] = x.materialTypes;
    }
}