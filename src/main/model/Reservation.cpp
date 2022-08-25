#include "Reservation.h"
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::Reservation& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Reservation & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {
    void from_json(const json & j, ereol::Reservation& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();
        x.bookId = j.at("bookid").get<std::string>();
        x.createdUtc = j.at("createdUtc").get<int64_t>();
        x.status = j.at("status").get<std::string>();
        x.expireUtc = j.at("expireUtc").get<int64_t>();
        x.expectedRedeemDateUtc = j.at("expectedRedeemDateUtc").get<int64_t>();     
    }

    void to_json(json & j, const ereol::Reservation & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;   
        j["bookid"] = x.bookId;
        j["createdUtc"] = x.createdUtc;
        j["status"] = x.status;
        j["expireUtc"] = x.expireUtc;
        j["expectedRedeemDateUtc"] = x.expectedRedeemDateUtc;        
    }
}
