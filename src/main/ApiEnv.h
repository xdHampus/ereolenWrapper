//
// Created by root on 1/29/22.
//

#ifndef EREOLENWRAPPER_APIENV_H
#define EREOLENWRAPPER_APIENV_H

#include <string>
#include <utility>
#include <vector>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "src/main/structs/Library.h"
#include "src/main/structs/RpcPayload.h"

namespace ereol {

    class ApiEnv {
    private:
        static const std::string apiKey;
        static std::string rpcEndpoint;
        static const std::string appVersion;
        static const std::string language;
    public:
        static std::string getApiKey() { return apiKey; }
        static std::string getRPC() { return rpcEndpoint; }
        //TODO: Remove setRPC and find another way to test mock endpoint
        static void setRPC(std::string endpoint){
            rpcEndpoint = std::move(endpoint);
        }
        static std::string getAppVersion() { return appVersion; }
        static std::string getLanguage() { return language; }

        static int getLibraryCount();
        static std::string getLibraryName(ereol::Library library);
        static std::string getLibraryCode(ereol::Library library);

        static std::optional<ereol::Library> getLibraryFromCode(std::string libraryCode);
        static nlohmann::json convertRpcPayloadToJSON(ereol::RpcPayload rpcPayload);
        static std::string getRpcPayloadJSON(std::string method, std::vector<std::string> params);

    };
}

#endif //EREOLENWRAPPER_APIENV_H
