#ifndef EREOLENWRAPPER_RESPONSE_H
#define EREOLENWRAPPER_RESPONSE_H

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
}
#endif //EREOLENWRAPPER_RESPONSE_H
