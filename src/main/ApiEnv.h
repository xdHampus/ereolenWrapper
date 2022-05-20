//
// Created by root on 1/29/22.
//

#ifndef EREOLENWRAPPER_APIENV_H
#define EREOLENWRAPPER_APIENV_H

#include "src/main/model/Library.h"
#include "src/main/model/RpcPayload.h"

#ifdef __cplusplus 
#include <string>
#include <utility>
#include <vector>
#include <optional>
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
        static std::string convertRpcPayloadToJSON(ereol::RpcPayload rpcPayload);
        static std::string getRpcPayloadJSON(std::string method, std::vector<std::string> params);

    };
#else
const char*  ereol_ApiEnv_getApiKey(); 
const char*  ereol_ApiEnv_getRPC(); 
void  ereol_ApiEnv_setRPC(char* endpoint); 
const char*  ereol_ApiEnv_getAppVersion(); 
const char*  ereol_ApiEnv_getLanguage(); 
int  ereol_ApiEnv_getLibraryCount(); 
const char*  ereol_ApiEnv_getLibraryName(Library* library); 
const char*  ereol_ApiEnv_getLibraryCode(Library* library); 
Library*  ereol_ApiEnv_getLibraryFromCode(char* libraryCode); 
const char*   ereol_ApiEnv_convertRpcPayloadToJSON(RpcPayload* rpcPayload); 
const char*   ereol_ApiEnv_getRpcPayloadJSON(char* method, char** params, size_t paramsN); 
#endif
#ifdef __cplusplus 
}
#endif
#endif //EREOLENWRAPPER_APIENV_H
