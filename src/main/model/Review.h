
#ifndef EREOLENWRAPPER_REVIEW_H
#define EREOLENWRAPPER_REVIEW_H

#include "Term.h"
#ifdef __cplusplus
#include <vector>
#include <string>
namespace ereol {
    struct Review {
        std::string source;
        std::string subTitle;
        std::string url;
    };
#else

#endif
#ifdef __cplusplus
    void from_json(const std::string  &s, ereol::Review& x);
    void to_json(std::string & s, const ereol::Review & x);
}
#endif

#endif //EREOLENWRAPPER_REVIEW_H
