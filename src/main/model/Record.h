#ifndef EREOLENWRAPPER_RECORD_H
#define EREOLENWRAPPER_RECORD_H

#include "Contributor.h"
#include "LoanIdentifier.h"
#include <optional>
#include <string>
#include <vector>

namespace ereol {
    struct Record {
        ereol::LoanIdentifier loanIdentifier;  
        std::string title;
        std::string publisher;
        std::string description;
        std::string language;
        std::string mediaType;

        std::optional<int64_t> createdDate = std::nullopt;
        std::optional<int64_t> updatedDate;
        std::optional<int64_t> firstPublished;
        std::optional<int64_t> duration;    

        std::optional<std::string> recordType;
        std::optional<std::string> cover;
        std::optional<std::string> phid;
        std::optional<std::string> format;
        std::optional<std::string> thumbnail;
        std::optional<std::string> abstract;
        std::optional<std::string> year;
        std::optional<std::string> edition;
        std::optional<std::string> shelfmark;
        std::optional<std::string> seriesPart;
        std::optional<std::string> subscription;
        std::optional<std::string> eReolenGlobalUrl;

        std::optional<std::vector<ereol::Contributor>> contributors;

        std::optional<std::vector<std::string>> creators;
        std::optional<std::vector<std::string>> series;
        std::optional<std::vector<std::string>> subjects;
        std::optional<std::vector<std::string>> types;
    };

    void from_json(const std::string  &s, ereol::Record& x);
    void to_json(std::string & s, const ereol::Record & x);

}

#endif //EREOLENWRAPPER_RECORD_H
