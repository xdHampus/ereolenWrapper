#include "Record.h"
#include <vector>

#include <cstdlib>
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::Record& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Record & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::Record& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();        
        x.title = j.at("title").get<std::string>();
        x.publisher = j.at("publisher").get<std::string>();
        x.description = j.at("description").get<std::string>();
        x.language = j.at("language").get<std::string>();
        x.mediaType = j.at("mediaType").get<std::string>();

        x.createdDate = ereol::get_optional<int64_t>(j, "createdDate");
        x.updatedDate = ereol::get_optional<int64_t>(j, "updatedDate");
        x.firstPublished = ereol::get_optional<int64_t>(j, "firstPublished");
        x.duration = ereol::get_optional<int64_t>(j, "duration");

        x.recordType = ereol::get_optional<std::string>(j, "icon");
        x.cover = ereol::get_optional<std::string>(j, "cover");
        x.phid = ereol::get_optional<std::string>(j, "phid");
        x.format = ereol::get_optional<std::string>(j, "format");
        x.thumbnail = ereol::get_optional<std::string>(j, "thumbnail");
        x.abstract = ereol::get_optional<std::string>(j, "abstract");
        x.year = ereol::get_optional<std::string>(j, "year");
        x.edition = ereol::get_optional<std::string>(j, "edition");
        x.shelfmark = ereol::get_optional<std::string>(j, "shelfmark");
        x.seriesPart = ereol::get_optional<std::string>(j, "seriesPart");
        x.subscription = ereol::get_optional<std::string>(j, "subscription");
        x.eReolenGlobalUrl = ereol::get_optional<std::string>(j, "eReolenGlobalUrl");

        x.contributors = ereol::get_optional<std::vector<ereol::Contributor>>(j, "contributors");

        x.creators = ereol::get_optional<std::vector<std::string>>(j, "creators");
        x.series = ereol::get_optional<std::vector<std::string>>(j, "series");
        x.subjects = ereol::get_optional<std::vector<std::string>>(j, "subjects");
        x.types = ereol::get_optional<std::vector<std::string>>(j, "types");
    }

    void to_json(json & j, const ereol::Record & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;
        j["title"] = x.title;
        j["publisher"] = x.publisher;
        j["description"] = x.description;
        j["language"] = x.language;
        j["mediaType"] = x.mediaType;

        j["createdDate"] = x.createdDate.value();
        j["updatedDate"] = x.updatedDate.value();
        j["firstPublished"] = x.firstPublished.value();
        j["duration"] = x.duration.value();

        j["icon"] = x.recordType.value();
        j["cover"] = x.cover.value();
        j["phid"] = x.phid.value();
        j["format"] = x.format.value();
        j["thumbnail"] = x.thumbnail.value();
        j["abstract"] = x.abstract.value();
        j["year"] = x.year.value();
        j["edition"] = x.edition.value();
        j["shelfmark"] = x.shelfmark.value();
        j["seriesPart"] = x.seriesPart.value();
        j["subscription"] = x.subscription.value();
        j["eReolenGlobalUrl"] = x.eReolenGlobalUrl.value();

        j["contributors"] = x.contributors.value();

        j["creators"] = x.creators.value();
        j["series"] = x.series.value();
        j["subjects"] = x.subjects.value();
        j["types"] = x.types.value();

    }

}