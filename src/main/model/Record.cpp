#include "Record.h"
#include <vector>

#include <cstdlib>
#include "../util/JSONHelper.h"
#include "../util/HelperFunctions.h"
#ifdef COMPILE_LUA
#include "../lua/LuaInterface.h"
#include <LuaBridge/Vector.h>
#include <LuaBridge/Optional.h>
#endif



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


        j["createdDate"] = ereol::or_else(x.createdDate, (int64_t) 0);
        j["updatedDate"] = ereol::or_else(x.updatedDate, (int64_t) 0);
        j["firstPublished"] = ereol::or_else(x.firstPublished, (int64_t) 0);
        j["duration"] = ereol::or_else(x.duration, (int64_t) 0);

        j["icon"] = ereol::or_else(x.recordType, std::string());
        j["cover"] = ereol::or_else(x.cover, std::string());
        j["phid"] = ereol::or_else(x.phid, std::string());
        j["format"] = ereol::or_else(x.format, std::string());
        j["thumbnail"] = ereol::or_else(x.thumbnail, std::string());
        j["abstract"] = ereol::or_else(x.abstract, std::string());
        j["year"] = ereol::or_else(x.year, std::string());
        j["edition"] = ereol::or_else(x.edition, std::string());
        j["shelfmark"] = ereol::or_else(x.shelfmark, std::string());
        j["seriesPart"] = ereol::or_else(x.seriesPart, std::string());
        j["subscription"] = ereol::or_else(x.subscription, std::string());
        j["eReolenGlobalUrl"] = ereol::or_else(x.eReolenGlobalUrl, std::string());

        j["contributors"] = ereol::or_else(x.contributors, std::vector<ereol::Contributor>());

        j["creators"] = ereol::or_else(x.creators, std::vector<std::string>());
        j["series"] = ereol::or_else(x.series, std::vector<std::string>());
        j["subjects"] = ereol::or_else(x.subjects, std::vector<std::string>());
        j["types"] = ereol::or_else(x.types, std::vector<std::string>());

    }

}

#ifdef COMPILE_LUA
void ereol::luaRegisterRecord(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Record>("Record")
            .addConstructor <void (*) (void)> ()
            .addProperty("loanIdentifier", &ereol::Record::loanIdentifier)
            .addProperty("title", &ereol::Record::title)
            .addProperty("publisher", &ereol::Record::publisher)
            .addProperty("description", &ereol::Record::description)
            .addProperty("language", &ereol::Record::language)
            .addProperty("mediaType", &ereol::Record::mediaType)
            .addProperty("createdDate", &ereol::Record::createdDate)
            .addProperty("updatedDate", &ereol::Record::updatedDate)
            .addProperty("firstPublished", &ereol::Record::firstPublished)
            .addProperty("duration", &ereol::Record::duration)
            .addProperty("recordType", &ereol::Record::recordType)
            .addProperty("cover", &ereol::Record::cover)
            .addProperty("phid", &ereol::Record::phid)
            .addProperty("format", &ereol::Record::format)
            .addProperty("thumbnail", &ereol::Record::thumbnail)
            .addProperty("abstract", &ereol::Record::abstract)
            .addProperty("year", &ereol::Record::year)
            .addProperty("edition", &ereol::Record::edition)
            .addProperty("shelfmark", &ereol::Record::shelfmark)
            .addProperty("seriesPart", &ereol::Record::seriesPart)
            .addProperty("subscription", &ereol::Record::subscription)
            .addProperty("eReolenGlobalUrl", &ereol::Record::eReolenGlobalUrl)
            .addProperty("contributors", &ereol::Record::contributors)
            .addProperty("creators", &ereol::Record::creators)
            .addProperty("series", &ereol::Record::series)
            .addProperty("subjects", &ereol::Record::subjects)
            .addProperty("types", &ereol::Record::types)
            .addFunction("toJson", std::function <std::string (const ereol::Record*)> (
                [] (const ereol::Record* o) {
                    std::string s; ereol::to_json(s,*o);
                    return s;
            }))
        .endClass()
    .endNamespace();
}
#endif