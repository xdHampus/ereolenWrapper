
#ifndef EREOLENWRAPPER_PAGERESULT_H
#define EREOLENWRAPPER_PAGERESULT_H

#include "Record.h"
#include "Facet.h"
#include <vector>

namespace ereol {
    struct PageResult {
        std::vector<std::vector<Record>> data;
        int count = 0;
        bool more = false;
        std::vector<ereol::Facet> facets;
    };
    void from_json(const std::string  &s, ereol::PageResult& x);
    void to_json(std::string & s, const ereol::PageResult & x);
}
#endif //EREOLENWRAPPER_PAGERESULT_H
