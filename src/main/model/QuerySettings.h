
#ifndef EREOLENWRAPPER_QUERYSETTINGS_H
#define EREOLENWRAPPER_QUERYSETTINGS_H

#include "Record.h"
#include "Facet.h"
#ifdef __cplusplus
#include <vector>
#include <optional>
#include <map>

namespace ereol {
    struct QuerySettings {
        int startIndex = 0;
        int endIndex = 20;
        std::optional<std::map<std::string, std::string>> facets;
    };
#else

#endif
#ifdef __cplusplus
}
#endif

#endif //EREOLENWRAPPER_QUERYSETTINGS_H
