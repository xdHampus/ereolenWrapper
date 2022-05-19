#pragma once
#include "Contributor.h"
#include <optional>
#include <string>
#include <vector>

namespace ereol {
    struct Product {
        std::string identifier;
        std::string isbn;        
        std::string title;
        std::string publisher;
        std::string description;
        std::string language;
        std::string mediaType;

        std::optional<uint64_t> createdDate;
        std::optional<uint64_t> updatedDate;
        std::optional<uint64_t> firstPublished;
        std::optional<uint64_t> duration;    

        std::optional<std::string> productType;
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

        std::optional<std::vector<Contributor>> contributors;

        std::optional<std::vector<std::string>> creators;
        std::optional<std::vector<std::string>> series;
        std::optional<std::vector<std::string>> subjects;
        std::optional<std::vector<std::string>> types;
    };
}
