#ifndef EREOLENWRAPPER_CONTRIBUTOR_H
#define EREOLENWRAPPER_CONTRIBUTOR_H

#include <string>
namespace ereol {
    struct Contributor {
        std::string type;
        std::string composedName;
        std::string firstName;
        std::string lastName;
    };
    void from_json(const std::string  &s, ereol::Contributor& x);
    void to_json(std::string & s, const ereol::Contributor & x);
}
#endif //EREOLENWRAPPER_CONTRIBUTOR_H
