#ifndef EREOLENWRAPPER_CREATORINFO_H
#define EREOLENWRAPPER_CREATORINFO_H

#include <string>
namespace ereol {
    // getAboutCreators: an author portrait, usually from Forfatterweb. Same shape
    // as Review plus the creator's name, which matters when a title has several.
    struct CreatorInfo {
        std::string source;
        std::string creator;
        std::string subTitle;
        std::string url;
    };
    void from_json(const std::string  &s, ereol::CreatorInfo& x);
    void to_json(std::string & s, const ereol::CreatorInfo & x);
}
#endif //EREOLENWRAPPER_CREATORINFO_H
