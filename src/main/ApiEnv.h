//
// Created by root on 1/29/22.
//

#ifndef EREOLENWRAPPER_APIENV_H
#define EREOLENWRAPPER_APIENV_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace ereol {
    struct RpcPayload {
        std::string jsonrpc = "2.0";
        std::string method;
        std::vector<std::string> params;
        std::string id = "bf808188-c534-3369-3f00-5d8c1a389ccd";
    };
    class ApiEnv {
    private:
        inline static const std::string apiKey = "HgAMJJhTM5qp9Q3nElWE0P2yPrdOoc8N";
        inline static const std::string rpcEndpoint = "https://ereolen.redia.dk/v1/rpc.php/";
        inline static const std::string appVersion = "android_3.5.3";
        inline static const std::string language = "da";
    public:
        static std::string getApiKey() { return apiKey; }
        static std::string getRPC() { return rpcEndpoint; }
        static std::string getAppVersion() { return appVersion; }
        static std::string getLanguage() { return language; }
        static nlohmann::json convertRpcPayloadToJSON(RpcPayload rpcPayload){
            nlohmann::json j;

            j["jsonrpc"] = rpcPayload.jsonrpc;
            j["method"] = rpcPayload.method;
            j["params"] = rpcPayload.params;
            j["id"] = rpcPayload.id;

            return j;
        }
        static std::string getRpcPayloadJSON(std::string method, std::vector<std::string> params){
            RpcPayload rpcPayload;
            rpcPayload.method = method;
            rpcPayload.params = params;

            return convertRpcPayloadToJSON(rpcPayload).dump();
        }
    };
}

#endif //EREOLENWRAPPER_APIENV_H
