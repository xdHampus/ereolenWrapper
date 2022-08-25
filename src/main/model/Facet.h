
#ifndef EREOLENWRAPPER_FACET_H
#define EREOLENWRAPPER_FACET_H

#include "Term.h"
#ifdef __cplusplus
#include <vector>
#include <string>
namespace ereol {
    struct Facet {
        std::string name;
        std::vector<ereol::Term> terms;
        std::string type;
        std::string translationKey;
    };
#else

#endif
#ifdef __cplusplus
    void from_json(const std::string  &s, ereol::Facet& x);
    void to_json(std::string & s, const ereol::Facet & x);
}
#endif

#endif //EREOLENWRAPPER_FACET_H






/*
    inline void from_json(const json & j, ereol::Facet& x) {
        x.name = j.at("name").get<std::string>();
        x.terms = j.at("terms").get<std::vector<ereol::Term>>();
        x.type = j.at("type").get<std::string>();
        x.translationKey = j.at("translationKey").get<std::string>();
    }

    inline void to_json(json & j, const ereol::Facet & x) {
        j = json::object();
        j["name"] = x.name;
        j["terms"] = x.terms;
        j["type"] = x.type;
        j["translationKey"] = x.translationKey;
    }
 */