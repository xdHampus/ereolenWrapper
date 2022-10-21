#include <nlohmann/json.hpp>

#include <string>
#include <optional>

#include "../model/ChecklistItem.h"
#include "../model/Contributor.h"
#include "../model/LoanActive.h"
#include "../model/LoanHistorical.h"
#include "../model/LoanIdentifier.h"
#include "../model/Record.h"
#include "../model/Reservation.h"
#include "src/main/model/PageResult.h"
#include "src/main/model/Review.h"
#include "../model/LibraryProfile.h"


namespace ereol {
    template <typename T>
    inline std::optional<T> get_optional(const  nlohmann::json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return std::optional<T>(j.at(property).get<T>());
        }
        return std::optional<T>();
    }
    template <typename T>
    inline std::optional<T> get_optional(const  nlohmann::json & j, std::string property) {
        return get_optional<T>(j, property.data());
    }
}

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

    void from_json(const json & j, ereol::Record & x);
    void to_json(json & j, const ereol::Record & x);

    void from_json(const json & j, ereol::PageResult & x);
    void to_json(json & j, const ereol::PageResult & x);


    void from_json(const json & j, ereol::Reservation & x);
    void to_json(json & j, const ereol::Reservation & x);

    void from_json(const json & j, ereol::Facet & x);
    void to_json(json & j, const ereol::Facet & x);

    void from_json(const json & j, ereol::Term & x);
    void to_json(json & j, const ereol::Term & x);

    void from_json(const json & j, ereol::Review& x);
    void to_json(json & j, const ereol::Review & x);

    void from_json(const json & j, ereol::LibraryProfile& x);
    void to_json(json & j, const ereol::LibraryProfile & x);

/*


    void from_json(const json & j, ereol::Language & x);
    void to_json(json & j, const ereol::Language & x);

    void from_json(const json & j, ereol::MediaType & x);
    void to_json(json & j, const ereol::MediaType & x);

    void from_json(const json & j, ereol::RecordType & x);
    void to_json(json & j, const ereol::RecordType & x);


    inline void from_json(const json & j, ereol::RecordType & x) {
        if (j == "audiobook"    || j == "Lydbog") x = ereol::RecordType::AUDIOBOOK;
        else if (j == "ebook"   || j == "E-bog" ) x = ereol::RecordType::EBOOK;
        else if (j == "podcast" || j == "Podcast") x = ereol::RecordType::PODCAST;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const ereol::RecordType & x, bool icon) {
        switch (x) {
            case ereol::RecordType::AUDIOBOOK: j = icon ? "Lydbog"  : "audiobook"; break;
            case ereol::RecordType::EBOOK:     j = icon ? "E-bog"   : "ebook"; break;
            case ereol::RecordType::PODCAST:   j = icon ? "Podcast" : "podcast"; break;
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
