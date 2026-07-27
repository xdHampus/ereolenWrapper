#ifndef EREOLENWRAPPER_APICALLER_H
#define EREOLENWRAPPER_APICALLER_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "src/main/model/Token.h"
#include "src/main/model/Response.h"
#include "src/main/ApiEnv.h"
#include "ErrorResponse.h"
#include "SslOptions.h"

namespace ereol {
    class ApiCaller {
    private:
        static nlohmann::json handleResponse(const cpr::Response& r){
            if(r.status_code == 200) {
                auto jr = nlohmann::json::parse(r.text);
                if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
                    if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                        return  jr;
                    } else { //TODO: Invalid input or no result
                    }
                } else { //TODO: Handle API errors
                }
            } else { //TODO: Handle HTTP errors
            }
            return {};
        }
        template <typename T>
        static ereol::Response<T> handleResponse(const cpr::Response& r, ereol::Response<T> fallbackError){
            if(r.status_code == 200) {
                auto jr = nlohmann::json::parse(r.text);
                if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
                    if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                        return ereol::Response<T>({jr["result"]["data"].get<T>()});
                    } else { return fallbackError.withCode(ereol::ErrorResponse::resultCode(jr)); }
                } else { return ereol::ErrorResponse::genericErrorAPI<T>({}).withCode(ereol::ErrorResponse::resultCode(jr)); }
            } else { return ereol::ErrorResponse::genericErrorHTTP<T>({}); }
        }
        template <typename T>
        static ereol::Response<T> handleResponse(const cpr::Response& r){
            if(r.status_code == 200) {
                auto jr = nlohmann::json::parse(r.text);
                if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
                    if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                        return ereol::Response<T>({jr["result"]["data"].get<T>()});
                    } else { return ereol::ErrorResponse::invalidInput<T>().withCode(ereol::ErrorResponse::resultCode(jr)); }
                } else { return ereol::ErrorResponse::genericErrorAPI<T>({}).withCode(ereol::ErrorResponse::resultCode(jr)); }
            } else { return ereol::ErrorResponse::genericErrorHTTP<T>({}); }
        }
    public:
        static cpr::Response requestPost(std::string &payload){
            return cpr::Post(
                    cpr::Url{ereol::ApiEnv::getRPC()},
                    cpr::Body{payload},
                    cpr::Header{{"Content-Type", "text/plain"}},
                    ereol::sslOptions());
        }
        static cpr::Response requestPost(std::string &payload, ereol::Token &token){
            return cpr::Post(
                    cpr::Url{ereol::ApiEnv::getRPC()},
                    cpr::Body{payload},
                    cpr::Header{{"Content-Type", "text/plain"}},
                    cpr::Cookies{{"PHPSESSID", token.sessid}},
                    ereol::sslOptions());
        }
        template <typename T>
        static ereol::Response<T>  getResponse(std::string &payload) {
            return handleResponse<T>(requestPost(payload));
        }
        template <typename T>
        static ereol::Response<T> getResponse(std::string &payload, ereol::Token &token) {
            return handleResponse<T>(requestPost(payload, token));
        }
        template <typename T>
        static ereol::Response<T> getResponse(std::string &payload, ereol::Token &token, ereol::Response<T> fallbackError) {
            return handleResponse<T>(requestPost(payload, token), fallbackError);
        }

        static std::string defaultPayloadGenericJSON(std::string &method){
            return ereol::ApiEnv::getRpcPayloadJSON(
                    method,
                    {
                            ereol::ApiEnv::getApiKey(),
                            ereol::ApiEnv::getAppVersion(),
                            ereol::ApiEnv::getLanguage()
                    }
            );
        }
        static std::string defaultPayloadJSON(std::string method, ereol::Library &library){
            return ereol::ApiEnv::getRpcPayloadJSON(
                    method,
                    {
                            ereol::ApiEnv::getApiKey(),
                            ereol::ApiEnv::getAppVersion(),
                            ereol::ApiEnv::getLanguage(),
                            ereol::ApiEnv::getLibraryCode(library)
                    }
            );
        }
        // Several methods take an array where a single identifier would go.
        static std::string defaultPayloadIdentifiersJSON(const std::string &method, const std::vector<std::string> &identifiers, const ereol::Library &library){
            nlohmann::json j;
            j["jsonrpc"] = "2.0";
            j["method"] = method;
            j["params"] = std::vector<std::string> {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(library),
            };
            j["params"][4] = identifiers;
            j["id"] = ereol::RpcPayload().id;
            return j.dump();
        }

        // Write methods answer with result.result and a data field that is often
        // null, so Response<bool> cannot go through the templated handler --
        // which requires data to be present.
        static ereol::Response<bool> getAck(std::string &payload, ereol::Token &token){
            cpr::Response r = requestPost(payload, token);
            if(r.status_code != 200) { return ereol::ErrorResponse::genericErrorHTTP<bool>({}); }

            auto jr = nlohmann::json::parse(r.text, nullptr, false);
            if(jr.is_discarded()) { return ereol::ErrorResponse::genericErrorAPI<bool>("Malformed response"); }

            if(jr["result"] == nullptr || jr["result"]["result"] == nullptr) {
                return ereol::ErrorResponse::genericErrorAPI<bool>({}).withCode(ereol::ErrorResponse::resultCode(jr));
            }
            if(!jr["result"]["result"].get<bool>()) {
                return ereol::ErrorResponse::invalidInput<bool>().withCode(ereol::ErrorResponse::resultCode(jr));
            }
            return ereol::Response<bool>(true);
        }

        static std::string defaultPayloadIdentifierJSON(std::string method, std::string identifier, ereol::Library &library){
            return ereol::ApiEnv::getRpcPayloadJSON(
                    method,
                    {
                            ereol::ApiEnv::getApiKey(),
                            ereol::ApiEnv::getAppVersion(),
                            ereol::ApiEnv::getLanguage(),
                            ereol::ApiEnv::getLibraryCode(library),
                            identifier
                    }
            );
        }
        static std::string defaultPayloadIdentifierConfiguredJSON(std::string method, std::string identifier, ereol::Library &library,const ereol::QuerySettings &settings){
            return ereol::ApiEnv::getRpcPayloadJSON(
                    method,
                    {
                            ereol::ApiEnv::getApiKey(),
                            ereol::ApiEnv::getAppVersion(),
                            ereol::ApiEnv::getLanguage(),
                            ereol::ApiEnv::getLibraryCode(library),
                            identifier
                    },
                    settings
            );
        }
        static std::string defaultPayloadConfiguredJSON(const std::string &method, const ereol::Library &library,const ereol::QuerySettings &settings){
            return ereol::ApiEnv::getRpcPayloadJSON(
                    method,
                    {
                            ereol::ApiEnv::getApiKey(),
                            ereol::ApiEnv::getAppVersion(),
                            ereol::ApiEnv::getLanguage(),
                            ereol::ApiEnv::getLibraryCode(library)
                    },
                    settings
            );
        }
    };
}



#endif //EREOLENWRAPPER_APICALLER_H

