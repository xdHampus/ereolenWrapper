#ifndef EREOLENWRAPPER_APIENV_H
#define EREOLENWRAPPER_APIENV_H

#include "model/Library.h"
#include "model/RpcPayload.h"
#include "model/QuerySettings.h"

#include <string>
#include <utility>
#include <vector>
#include <optional>
namespace ereol {

    class ApiEnv {
    public:
        //LIBRARY
        static std::string getApiKey();
        static std::string getRPC();
        //TODO: Remove setRPC and find another way to test mock endpoint
        static void setRPC(std::string endpoint);
        static std::string getAppVersion();
        static void setAppVersion(std::string version);
        // Live getSupportedVersion probe. Returns "" when the call fails.
        static std::string getRequiredAppVersion();
        // Sets appVersion from the server's requiredVersion. False when unreachable.
        static bool syncAppVersion();
        static std::string getLanguage();
        // Absolute path to a PEM CA bundle for TLS verification. Empty means
        // "use whatever the TLS backend defaults to", which is right on a
        // desktop with a system trust store. On a device that has none -- a
        // Kobo, say -- point this at the bundle the host application ships.
        static std::string getCaBundle();
        static void setCaBundle(std::string path);
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
