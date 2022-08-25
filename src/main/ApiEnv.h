#ifndef EREOLENWRAPPER_APIENV_H
#define EREOLENWRAPPER_APIENV_H

#include "src/main/model/Library.h"
#include "src/main/model/RpcPayload.h"
#include "src/main/model/QuerySettings.h"

#include <string>
#include <utility>
#include <vector>
#include <optional>
namespace ereol {

    class ApiEnv {
    public:
        static std::string getApiKey();
        static std::string getRPC();
        //TODO: Remove setRPC and find another way to test mock endpoint
        static void setRPC(std::string endpoint);
        static std::string getAppVersion();
        static std::string getLanguage();

        static int getLibraryCount();
        static std::string getLibraryName(ereol::Library library);
        static std::string getLibraryCode(ereol::Library library);

        static std::optional<ereol::Library> getLibraryFromCode(std::string libraryCode);
        static std::string convertRpcPayloadToJSON(ereol::RpcPayload rpcPayload);
        static std::string convertRpcPayloadToJSON(ereol::RpcPayload rpcPayload, ereol::QuerySettings settings);
        static std::string getRpcPayloadJSON(std::string method, std::vector<std::string> params);
        static std::string getRpcPayloadJSON(std::string method, std::vector<std::string> params, ereol::QuerySettings settings);

    };
}
#endif //EREOLENWRAPPER_APIENV_H
