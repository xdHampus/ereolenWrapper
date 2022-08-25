
#ifndef EREOLENWRAPPER_RESPONSE_H
#define EREOLENWRAPPER_RESPONSE_H

#ifdef __cplusplus
#include <vector>
#include <string>
namespace ereol {
    template <typename T>
    struct Response {
        bool success;
        //message
        //error
        T data;
    };
#else

#endif
#ifdef __cplusplus
}
#endif

#endif //EREOLENWRAPPER_RESPONSE_H

//