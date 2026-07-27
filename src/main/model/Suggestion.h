#ifndef EREOLENWRAPPER_SUGGESTION_H
#define EREOLENWRAPPER_SUGGESTION_H

#include <string>
namespace ereol {
    // getSuggestions: one search-typeahead completion. `facet` says what kind of
    // thing it is (e.g. redia.subject, redia.creator) and translationKey is the
    // app's label for that kind.
    struct Suggestion {
        std::string facet;
        std::string translationKey;
        std::string suggestion;
    };
    void from_json(const std::string  &s, ereol::Suggestion& x);
    void to_json(std::string & s, const ereol::Suggestion & x);
}
#endif //EREOLENWRAPPER_SUGGESTION_H
