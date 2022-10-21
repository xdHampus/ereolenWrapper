
#ifndef EREOLENWRAPPER_FACET_H
#define EREOLENWRAPPER_FACET_H

#include "Term.h"
#include <vector>
#include <string>

namespace ereol {
    struct Facet {
        std::string name;
        std::vector<ereol::Term> terms;
        std::string type;
        std::string translationKey;
    };

    void from_json(const std::string  &s, ereol::Facet& x);
    void to_json(std::string & s, const ereol::Facet & x);
}

#endif //EREOLENWRAPPER_FACET_H
