// Generators.h

//  To parse this JSON data, first install
//
//      json.h  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Generators.h data = nlohmann::json::parse(jsonString);


#include <nlohmann/json.hpp>

#include "../model/ChecklistItem.h"
#include "../model/Contributor.h"
#include "../model/LoanActive.h"
#include "../model/LoanHistorical.h"
#include "../model/LoanIdentifier.h"
#include "../model/Product.h"
#include "../model/Reservation.h"

namespace nlohmann {

    void from_json(const json & j, ereol::ChecklistItem & x);
    void to_json(json & j, const ereol::ChecklistItem & x);

    void from_json(const json & j, ereol::Contributor & x);
    void to_json(json & j, const ereol::Contributor & x);

    void from_json(const json & j, ereol::LoanActive & x);
    void to_json(json & j, const ereol::LoanActive & x);

    void from_json(const json & j, ereol::LoanHistorical & x);
    void to_json(json & j, const ereol::LoanHistorical & x);

    void from_json(const json & j, ereol::LoanIdentifier & x);
    void to_json(json & j, const ereol::LoanIdentifier & x);

    void from_json(const json & j, ereol::Product & x);
    void to_json(json & j, const ereol::Product & x);

    void from_json(const json & j, ereol::Reservation & x);
    void to_json(json & j, const ereol::Reservation & x);



/*


    void from_json(const json & j, ereol::Language & x);
    void to_json(json & j, const ereol::Language & x);

    void from_json(const json & j, ereol::MediaType & x);
    void to_json(json & j, const ereol::MediaType & x);

    void from_json(const json & j, ereol::ProductType & x);
    void to_json(json & j, const ereol::ProductType & x);








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