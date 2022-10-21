#ifndef EREOLENWRAPPER_TERM_H
#define EREOLENWRAPPER_TERM_H

#include <string>
namespace ereol {
    struct Term {
        std::string term;
        std::string value;
        int64_t quantity = 0;
    };
    void from_json(const std::string  &s, ereol::Term& x);
    void to_json(std::string & s, const ereol::Term & x);
}
#endif //EREOLENWRAPPER_TERM_H
