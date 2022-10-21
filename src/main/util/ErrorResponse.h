#ifndef EREOLENWRAPPER_ERRORRESPONSE_H
#define EREOLENWRAPPER_ERRORRESPONSE_H
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "src/main/model/Token.h"
#include "src/main/model/Response.h"
#include "src/main/ApiEnv.h"

namespace ereol {
    class ErrorResponse {
    public:

        template <typename T>
        static ereol::Response<T> genericErrorAPI(std::optional<std::string> detailedMessage) {
            return Response<T>({}, "API Error", false, detailedMessage);
        }
        template <typename T>
        static ereol::Response<T> genericErrorHTTP(std::optional<std::string> detailedMessage) {
            return Response<T>({}, "HTTP Error", false, detailedMessage);
        }
        template <typename T>
        static ereol::Response<T> incorrectCredentials() {
            return Response<T>({}, "Incorrect credentials", false);
        }
        template <typename T>
        static ereol::Response<T> invalidSessionID() {
            return Response<T>({}, "Session-ID not authenticated or incorrect", false);
        }
        template <typename T>
        static ereol::Response<T> invalidInput() {
            return Response<T>({}, "No result or invalid input", false);
        }


    };
}

#endif //EREOLENWRAPPER_ERRORRESPONSE_H
