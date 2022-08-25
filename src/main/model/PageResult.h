
#ifndef EREOLENWRAPPER_PAGERESULT_H
#define EREOLENWRAPPER_PAGERESULT_H

#include "Record.h"
#include "Facet.h"
#include <vector>

namespace ereol {
    struct PageResult {
        std::vector<std::vector<Record>> data;
        int count;
        bool more;
        std::vector<ereol::Facet> facets;
    };
    void from_json(const std::string  &s, ereol::PageResult& x);
    void to_json(std::string & s, const ereol::PageResult & x);
}
#endif //EREOLENWRAPPER_PAGERESULT_H

/*
    inline void from_json(const json & j, ereol::Data& x) {
        x.count = j.at("count").get<int64_t>();
        x.more = j.at("more").get<bool>();
        x.collections = j.at("collections").get<std::vector<ereol::Collection>>();
        x.facets = j.at("facets").get<std::vector<ereol::Facet>>();
    }

    inline void to_json(json & j, const ereol::Data & x) {
        j = json::object();
        j["count"] = x.count;
        j["more"] = x.more;
        j["collections"] = x.collections;
        j["facets"] = x.facets;
    }
*/