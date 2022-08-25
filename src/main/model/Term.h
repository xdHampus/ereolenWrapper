#ifndef EREOLENWRAPPER_TERM_H
#define EREOLENWRAPPER_TERM_H

#ifdef __cplusplus
#include <string>
namespace ereol {
    struct Term {
        std::string term;
        std::string value;
        int64_t quantity;
    };
#else

#endif
#ifdef __cplusplus
    void from_json(const std::string  &s, ereol::Term& x);
    void to_json(std::string & s, const ereol::Term & x);
}
#endif

#endif //EREOLENWRAPPER_TERM_H
/*

    inline void from_json(const json & j, ereol::Term& x) {
        x.term = j.at("term").get<std::string>();
        x.value = j.at("value").get<std::string>();
        x.quantity = j.at("quantity").get<int64_t>();
    }

    inline void to_json(json & j, const ereol::Term & x) {
        j = json::object();
        j["term"] = x.term;
        j["value"] = x.value;
        j["quantity"] = x.quantity;
    }

*/