#ifndef EREOLENWRAPPER_APICALLER_H
#define EREOLENWRAPPER_APICALLER_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "src/main/model/Token.h"
#include "src/main/model/Response.h"
#include "src/main/ApiEnv.h"

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
        static ereol::Response<T> handleResponse(const cpr::Response& r){
            ereol::Response<T> response = {};
            if(r.status_code == 200) {
                auto jr = nlohmann::json::parse(r.text);
                if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
                    if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                        response.data = jr["result"]["data"].get<T>();
                        response.success = true;
                    } else { //TODO: Invalid input or no result
                        response.success = false;
                    }
                } else { //TODO: Handle API errors
                    response.success = false;
                }
            } else { //TODO: Handle HTTP errors
                response.success = false;
            }
            return response;
        }
        static cpr::Response requestPost(std::string &payload){
            return cpr::Post(
                    cpr::Url{ereol::ApiEnv::getRPC()},
                    cpr::Body{payload},
                    cpr::Header{{"Content-Type", "text/plain"}});
        }
        static cpr::Response requestPost(std::string &payload, ereol::Token &token){
            return cpr::Post(
                    cpr::Url{ereol::ApiEnv::getRPC()},
                    cpr::Body{payload},
                    cpr::Header{{"Content-Type", "text/plain"}},
                    cpr::Cookies{{"PHPSESSID", token.sessid}});
        }
    public:
        static nlohmann::json getResponse(std::string &payload){
            return handleResponse(requestPost(payload));
        }
        template <typename T>
        static ereol::Response<T>  getResponse(std::string &payload) {
            return handleResponse<T>(requestPost(payload));
        }

        static nlohmann::json getResponse(std::string &payload, ereol::Token &token) {
            return handleResponse(requestPost(payload, token));
        }
        template <typename T>
        static ereol::Response<T> getResponse(std::string &payload, ereol::Token &token) {
            return handleResponse<T>(requestPost(payload, token));
        }
    };
}


#endif //EREOLENWRAPPER_APICALLER_H
