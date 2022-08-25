#ifndef EREOLENWRAPPER_REVIEW_H
#define EREOLENWRAPPER_REVIEW_H

#include "Term.h"
#include <vector>
#include <string>
namespace ereol {
    struct Review {
        std::string source;
        std::string subTitle;
        std::string url;
    };
    void from_json(const std::string  &s, ereol::Review& x);
    void to_json(std::string & s, const ereol::Review & x);
}
#endif //EREOLENWRAPPER_REVIEW_H
