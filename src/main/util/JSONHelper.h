// Generators.h

//  To parse this JSON data, first install
//
//      json.h  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Generators.h data = nlohmann::json::parse(jsonString);


#include <nlohmann/json.hpp>

#include "../structs/ChecklistItem.h"

/*
#include "../structs/LoanActive.h"
#include "../structs/LibraryProfile.h"
#include "../structs/Reservation.h"
#include "../structs/LoanHistorical.h"
#include "../structs/Product.h"
#include "../structs/ProductType.h"
#include "../structs/MediaType.h"
#include "../structs/Contributor.h"
*/

namespace nlohmann {

    void from_json(const json & j, ereol::ChecklistItem & x);
    void to_json(json & j, const ereol::ChecklistItem & x);
    /*
    void from_json(const json & j, ereol::Contributor & x);
    void to_json(json & j, const ereol::Contributor & x);

    void from_json(const json & j, ereol::Product & x);
    void to_json(json & j, const ereol::Product & x);

    void from_json(const json & j, ereol::LoanHistoryElement & x);
    void to_json(json & j, const ereol::LoanHistoryElement & x);

    void from_json(const json & j, ereol::Reservation & x);
    void to_json(json & j, const ereol::Reservation & x);


    void from_json(const json & j, ereol::LibraryProfile & x);
    void to_json(json & j, const ereol::LibraryProfile & x);

    void from_json(const json & j, ereol::Loan & x);
    void to_json(json & j, const ereol::Loan & x);

    void from_json(const json & j, ereol::Language & x);
    void to_json(json & j, const ereol::Language & x);

    void from_json(const json & j, ereol::MediaType & x);
    void to_json(json & j, const ereol::MediaType & x);

    void from_json(const json & j, ereol::ProductType & x);
    void to_json(json & j, const ereol::ProductType & x);

*/



/*

    inline void from_json(const json & j, ereol::Contributor& x) {
        x.type = j.at("type").get<std::string>();
        x.composedName = j.at("composedName").get<std::string>();
        x.firstName = j.at("firstName").get<std::string>();
        x.lastName = j.at("lastName").get<std::string>();
    }

    inline void to_json(json & j, const ereol::Contributor & x) {
        j = json::object();
        j["type"] = x.type;
        j["composedName"] = x.composedName;
        j["firstName"] = x.firstName;
        j["lastName"] = x.lastName;
    }

    inline void from_json(const json & j, ereol::Product& x) {
        x.identifier = j.at("identifier").get<std::string>();
        x.title = j.at("title").get<std::string>();
        x.publisher = j.at("publisher").get<std::string>();
        x.createdDate = ereol::get_optional<uint64_t>(j, "createdDate");
        x.updatedDate = ereol::get_optional<uint64_t>(j, "updatedDate");
        x.cover = ereol::get_optional<std::string>(j, "cover");
        x.thumbnail = ereol::get_optional<std::string>(j, "thumbnail");
        x.contributors = ereol::get_optional<std::vector<ereol::Contributor>>(j, "contributors");
        x.description = j.at("description").get<std::string>();
        x.isbn = j.at("isbn").get<std::string>();
        x.phid = ereol::get_optional<std::string>(j, "phid");
        x.firstPublished = ereol::get_optional<uint64_t>(j, "firstPublished");
        x.language = j.at("language").get<std::string>();
        x.duration = ereol::get_optional<uint64_t>(j, "duration");
        x.format = ereol::get_optional<std::string>(j, "format");
        x.mediaType = j.at("mediaType").get<std::string>();
        x.creators = ereol::get_optional<std::vector<std::string>>(j, "creators");
        x.abstract = ereol::get_optional<std::string>(j, "abstract");
        x.series = ereol::get_optional<std::vector<std::string>>(j, "series");
        x.year = ereol::get_optional<std::string>(j, "year");
        x.edition = ereol::get_optional<std::string>(j, "edition");
        x.subjects = ereol::get_optional<std::vector<std::string>>(j, "subjects");
        x.types = ereol::get_optional<std::vector<std::string>>(j, "types");
        x.shelfmark = ereol::get_optional<std::string>(j, "shelfmark");
        x.productType = ereol::get_optional<std::string>(j, "icon");
        x.seriesPart = ereol::get_optional<std::string>(j, "seriesPart");
        x.subscription = ereol::get_optional<std::string>(j, "subscription");
        x.eReolenGlobalUrl = ereol::get_optional<std::string>(j, "eReolenGlobalUrl");
    }

    inline void to_json(json & j, const ereol::Product & x) {
        j = json::object();
        j["identifier"] = x.identifier;
        j["title"] = x.title;
        j["publisher"] = x.publisher;
        j["createdDate"] = x.createdDate;
        j["updatedDate"] = x.updatedDate;
        j["cover"] = x.cover;
        j["thumbnail"] = x.thumbnail;
        j["contributors"] = x.contributors;
        j["description"] = x.description;
        j["isbn"] = x.isbn;
        j["phid"] = x.phid;
        j["firstPublished"] = x.firstPublished;
        j["language"] = x.language;
        j["duration"] = x.duration;
        j["format"] = x.format;
        j["mediaType"] = x.mediaType;
        j["creators"] = x.creators;
        j["abstract"] = x.abstract;
        j["series"] = x.series;
        j["year"] = x.year;
        j["edition"] = x.edition;
        j["subjects"] = x.subjects;
        j["types"] = x.types;
        j["shelfmark"] = x.shelfmark;
        j["icon"] = x.icon;
        j["seriesPart"] = x.seriesPart;
        j["subscription"] = x.subscription;
        j["eReolenGlobalUrl"] = x.eReolenGlobalUrl;
    }

    inline void from_json(const json & j, ereol::LoanHistoryElement& x) {
        x.loanId = j.at("loanId").get<std::string>();
        x.identifier = j.at("identifier").get<std::string>();
        x.loanDate = j.at("loanDate").get<uint64_t>();
        x.manuallyAdded = j.at("manuallyAdded").get<bool>();
        x.isbn = j.at("isbn").get<std::string>();
        x.title = j.at("title").get<std::string>();
        x.creator = j.at("creator").get<std::string>();
        x.publicationDate = j.at("publicationDate").get<std::string>();
        x.materialTypes = j.at("materialTypes").get<std::vector<std::string>>();
    }

    inline void to_json(json & j, const ereol::LoanHistoryElement & x) {
        j = json::object();
        j["loanId"] = x.loanId;
        j["identifier"] = x.identifier;
        j["loanDate"] = x.loanDate;
        j["manuallyAdded"] = x.manuallyAdded;
        j["isbn"] = x.isbn;
        j["title"] = x.title;
        j["creator"] = x.creator;
        j["publicationDate"] = x.publicationDate;
        j["materialTypes"] = x.materialTypes;
    }

    inline void from_json(const json & j, ereol::Reservation& x) {
        x.identifier = j.at("identifier").get<std::string>();
        x.isbn = j.at("isbn").get<std::string>();
        x.bookid = j.at("bookid").get<std::string>();
        x.createdUtc = j.at("createdUtc").get<uint64_t>();
        x.status = j.at("status").get<std::string>();
        x.expireUtc = j.at("expireUtc").get<uint64_t>();
        x.expectedRedeemDateUtc = j.at("expectedRedeemDateUtc").get<uint64_t>();
    }

    inline void to_json(json & j, const ereol::Reservation & x) {
        j = json::object();
        j["identifier"] = x.identifier;
        j["isbn"] = x.isbn;
        j["bookid"] = x.bookid;
        j["createdUtc"] = x.createdUtc;
        j["status"] = x.status;
        j["expireUtc"] = x.expireUtc;
        j["expectedRedeemDateUtc"] = x.expectedRedeemDateUtc;
    }

    inline void from_json(const json & j, ereol::ChecklistItem& x) {
        x.identifier = j.at("identifier").get<std::string>();
        x.isbn = j.at("isbn").get<std::string>();
        x.creationDateUtc = j.at("creationDateUtc").get<uint64_t>();
    }

    inline void to_json(json & j, const ereol::ChecklistItem & x) {
        j = json::object();
        j["identifier"] = x.identifier;
        j["isbn"] = x.isbn;
        j["creationDateUtc"] = x.creationDateUtc;
    }

    inline void from_json(const json & j, ereol::LibraryProfile& x) {
        x.maxConcurrentLoansPerBorrower = j.at("maxConcurrentLoansPerBorrower").get<uint>();
        x.maxConcurrentReservationsPerBorrower = j.at("maxConcurrentReservationsPerBorrower").get<uint>();
        x.maxConcurrentAudioLoansPerBorrower = j.at("maxConcurrentAudioLoansPerBorrower").get<uint>();
        x.maxConcurrentAudioReservationsPerBorrower = j.at("maxConcurrentAudioReservationsPerBorrower").get<uint>();
    }

    inline void to_json(json & j, const ereol::LibraryProfile & x) {
        j = json::object();
        j["maxConcurrentLoansPerBorrower"] = x.maxConcurrentLoansPerBorrower;
        j["maxConcurrentReservationsPerBorrower"] = x.maxConcurrentReservationsPerBorrower;
        j["maxConcurrentAudioLoansPerBorrower"] = x.maxConcurrentAudioLoansPerBorrower;
        j["maxConcurrentAudioReservationsPerBorrower"] = x.maxConcurrentAudioReservationsPerBorrower;
    }

    inline void from_json(const json & j, ereol::Loan& x) {
        x.identifier = j.at("identifier").get<std::string>();
        x.isbn = j.at("isbn").get<std::string>();
        x.retailerOrderNumber = j.at("retailerOrderNumber").get<std::string>();
        x.internalOrderNumber = j.at("internalOrderNumber").get<std::string>();
        x.orderDate = j.at("orderDate").get<uint64_t>();
        x.expireDate = j.at("expireDate").get<uint64_t>();
        x.downloadUrl = j.at("downloadUrl").get<std::string>();
        x.isSubscription = j.at("isSubscription").get<bool>();
    }

    inline void to_json(json & j, const ereol::Loan & x) {
        j = json::object();
        j["identifier"] = x.identifier;
        j["isbn"] = x.isbn;
        j["retailerOrderNumber"] = x.retailerOrderNumber;
        j["internalOrderNumber"] = x.internalOrderNumber;
        j["orderDate"] = x.orderDate;
        j["expireDate"] = x.expireDate;
        j["downloadUrl"] = x.downloadUrl;
        j["isSubscription"] = x.isSubscription;
    }

    inline void from_json(const json & j, ereol::ProductType & x) {
        if (j == "audiobook"    || j == "Lydbog") x = ereol::ProductType::AUDIOBOOK;
        else if (j == "ebook"   || j == "E-bog" ) x = ereol::ProductType::EBOOK;
        else if (j == "podcast" || j == "Podcast") x = ereol::ProductType::PODCAST;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const ereol::ProductType & x, bool icon) {
        switch (x) {
            case ereol::ProductType::AUDIOBOOK: j = icon ? "Lydbog"  : "audiobook"; break;
            case ereol::ProductType::EBOOK:     j = icon ? "E-bog"   : "ebook"; break;
            case ereol::ProductType::PODCAST:   j = icon ? "Podcast" : "podcast"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, ereol::MediaType & x) {
        if (j == "audio") x = ereol::MediaType::AUDIO;
        else if (j == "text") x = ereol::MediaType::TEXT;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const ereol::MediaType & x) {
        switch (x) {
            case ereol::MediaType::AUDIO: j = "audio"; break;
            case ereol::MediaType::TEXT: j = "text"; break;
            default: throw "This should not happen";
        }
    }
    */

}