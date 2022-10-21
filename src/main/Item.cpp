#include "Item.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "ApiEnv.h"
#include "util/JSONHelper.h"
#include "util/ApiCaller.h"
#ifdef COMPILE_LUA
#include "lua/LuaInterface.h"
#include <LuaBridge/Vector.h>
#include <LuaBridge/Optional.h>
#include <LuaBridge/Map.h>
#include "lua/ResponseLua.h"
#endif

const std::string otherTypesOfSameTitleMethod = "getOtherTypesOfSameTitle";
const std::string moreOfSameGenreMethod = "getMoreOfSameGenre";
const std::string moreOfSameCreatorMethod = "getMoreOfSameCreator";
const std::string moreInSameSeriesMethod = "getMoreInSameSeries";
const std::string somethingSimilarMethod = "getSomethingSimilar";
const std::string aboutCreatorsMethod = "getAboutCreators";
const std::string reviewsMethod = "getReviews";
const std::string coversMethod = "getCovers";
const std::string personalRecommendationsMethod = "getPersonalRecommendations";
const std::string loanStatusesMethod = "ereolen.getLoanStatuses";
const std::string productMethod = "getProduct";
const std::string recordsMethod = "getRecordsByIdentifiers";
const std::string searchMethod = "search";

ereol::Response<std::vector<ereol::Record>> ereol::Item::getOthersOfSameTitle(std::string identifier, ereol::Token token){
    std::string payloadJson = ereol::ApiCaller::defaultPayloadIdentifierJSON(otherTypesOfSameTitleMethod, identifier, token.library);
    cpr::Response r = ereol::ApiCaller::requestPost(payloadJson, token);

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);
        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                std::vector<ereol::Record> results = {};

                if(jr["result"]["data"]["ebook"] != nullptr){
                    results.push_back(jr["result"]["data"]["ebook"].get<ereol::Record>());
                }
                if(jr["result"]["data"]["audiobook"] != nullptr){
                    results.push_back(jr["result"]["data"]["audiobook"].get<ereol::Record>());
                }
                return ereol::Response<std::vector<ereol::Record>>(results);
            } else { return ereol::ErrorResponse::invalidInput<std::vector<ereol::Record>>(); }
        } else { return ereol::ErrorResponse::genericErrorAPI<std::vector<ereol::Record>>({}); }
    } else { return ereol::ErrorResponse::genericErrorHTTP<std::vector<ereol::Record>>({}); }
}

ereol::Response<ereol::PageResult> ereol::Item::getMoreOfSameGenre(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadIdentifierConfiguredJSON(moreOfSameGenreMethod, identifier, token.library, settings);
    return ereol::ApiCaller::getResponse<ereol::PageResult>(payloadJson, token);
}

ereol::Response<ereol::PageResult>
ereol::Item::getMoreOfSameCreator(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadIdentifierConfiguredJSON(moreOfSameCreatorMethod, identifier, token.library, settings);
    return ereol::ApiCaller::getResponse<ereol::PageResult>(payloadJson, token);
}

ereol::Response<ereol::PageResult> ereol::Item::getMoreInSameSeries(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadIdentifierConfiguredJSON(moreInSameSeriesMethod, identifier, token.library, settings);
    return ereol::ApiCaller::getResponse<ereol::PageResult>(payloadJson, token);
}

ereol::Response<std::vector<ereol::Record>> ereol::Item::getSomethingSimilar(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadIdentifierConfiguredJSON(somethingSimilarMethod, identifier, token.library, settings);
    return ereol::ApiCaller::getResponse<std::vector<ereol::Record>>(payloadJson, token);
}
//TODO: Not implemented correctly
ereol::Response<std::vector<ereol::Record>> ereol::Item::getPersonalRecommendations(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    return ereol::Response<std::vector<ereol::Record>>("Error",false);
    /*
     std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            personalRecommendationsMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    identifier
            },
            settings
    );
    ereol::Response<std::vector<ereol::Record>> response = ereol::ApiCaller::getResponse<std::vector<ereol::Record>>(payloadJson, token);
    return response.data;
     */
}

ereol::Response<std::vector<ereol::Review>> ereol::Item::getReviews(std::string identifier, ereol::Token token) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadIdentifierJSON(reviewsMethod, identifier, token.library);
    return ereol::ApiCaller::getResponse<std::vector<ereol::Review>>(payloadJson, token);
}


ereol::Response<std::map<std::string, std::string>> ereol::Item::getCoverUrls(std::vector<std::string> identifiers, ereol::Token token) {
    ereol::RpcPayload rpcPayload;
    rpcPayload.method = coversMethod;
    rpcPayload.params = std::vector<std::string> {
            ereol::ApiEnv::getApiKey(),
            ereol::ApiEnv::getAppVersion(),
            ereol::ApiEnv::getLanguage(),
            ereol::ApiEnv::getLibraryCode(token.library),
    };

    nlohmann::json j, jr;
    j["jsonrpc"] = rpcPayload.jsonrpc;
    j["method"] = rpcPayload.method;
    j["params"] = rpcPayload.params;
    j["params"][4] = identifiers;
    j["id"] = rpcPayload.id;
    std::string payloadJson = j.dump();
    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);
        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                std::map<std::string, std::string> result;
                for (const auto& item : jr["result"]["data"].items())
                {
                    if(item.value()["result"] != nullptr &&
                       item.value()["result"].get<bool>() &&
                       item.value()["data"] != nullptr &&
                       item.value()["data"]["url"] != nullptr){
                        result.insert(std::pair<std::string, std::string>(item.key(), item.value()["data"]["url"].get<std::string>()));
                    }
                }
                return ereol::Response<std::map<std::string, std::string>>(result);
            } else { return ereol::ErrorResponse::invalidInput<std::map<std::string, std::string>>(); }
        } else { return ereol::ErrorResponse::genericErrorAPI<std::map<std::string, std::string>>({}); }
    } else { return ereol::ErrorResponse::genericErrorHTTP<std::map<std::string, std::string>>({}); }
}

ereol::Response<std::map<std::string, std::string>>
ereol::Item::getLoanStatuses(std::vector<std::string> identifiers, ereol::Token token) {
    ereol::RpcPayload rpcPayload;
    rpcPayload.method = loanStatusesMethod;
    rpcPayload.params = std::vector<std::string> {
            ereol::ApiEnv::getApiKey(),
            ereol::ApiEnv::getAppVersion(),
            ereol::ApiEnv::getLanguage(),
            ereol::ApiEnv::getLibraryCode(token.library),
    };

    nlohmann::json j, jr;
    j["jsonrpc"] = rpcPayload.jsonrpc;
    j["method"] = rpcPayload.method;
    j["params"] = rpcPayload.params;
    j["params"][4] = identifiers;
    j["id"] = rpcPayload.id;
    std::string payloadJson = j.dump();
    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);
        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                std::map<std::string, std::string> result;
                for (const auto& item : jr["result"]["data"].items())
                {
                    if(item.value()["result"] != nullptr &&
                       item.value()["result"].get<bool>() &&
                       item.value()["data"] != nullptr &&
                       item.value()["data"]["loanStatus"] != nullptr){
                        result.insert(std::pair<std::string, std::string>(item.key(), item.value()["data"]["loanStatus"].get<std::string>()));
                    }
                }
                return ereol::Response<std::map<std::string, std::string>>(result);
            } else { return ereol::ErrorResponse::invalidInput<std::map<std::string, std::string>>(); }
        } else { return ereol::ErrorResponse::genericErrorAPI<std::map<std::string, std::string>>({}); }
    } else { return ereol::ErrorResponse::genericErrorHTTP<std::map<std::string, std::string>>({}); }
}

ereol::Response<ereol::Record> ereol::Item::getProduct(std::string identifier, ereol::Token token) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadIdentifierJSON(productMethod, identifier, token.library);
   return ereol::ApiCaller::getResponse<ereol::Record>(payloadJson, token);
}

ereol::Response<ereol::PageResult> ereol::Item::search(std::string queryString, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiCaller::defaultPayloadIdentifierConfiguredJSON(searchMethod, queryString, token.library, settings);
    return ereol::ApiCaller::getResponse<ereol::PageResult>(payloadJson, token);
}

ereol::Response<std::map<std::string, ereol::Record>> ereol::Item::getRecords(std::vector<std::string> identifiers, ereol::Token token) {
    ereol::RpcPayload rpcPayload;
    rpcPayload.method = recordsMethod;
    rpcPayload.params = std::vector<std::string> {
            ereol::ApiEnv::getApiKey(),
            ereol::ApiEnv::getAppVersion(),
            ereol::ApiEnv::getLanguage(),
            ereol::ApiEnv::getLibraryCode(token.library),
    };

    nlohmann::json j, jr;
    j["jsonrpc"] = rpcPayload.jsonrpc;
    j["method"] = rpcPayload.method;
    j["params"] = rpcPayload.params;
    j["params"][4] = identifiers;
    j["id"] = rpcPayload.id;
    std::string payloadJson = j.dump();
    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});

    if(r.status_code == 200) {
        auto jr = nlohmann::json::parse(r.text);
        if(jr["result"] != nullptr && jr["result"]["result"] != nullptr){
            if(jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
                std::map<std::string, ereol::Record> result;
                for (const auto& item : jr["result"]["data"].items())
                {
                    if(item.value()["result"] != nullptr &&
                       item.value()["result"].get<bool>() &&
                       item.value()["data"] != nullptr){
                        result.insert(std::pair<std::string, ereol::Record>(item.key(), item.value()["data"].get<ereol::Record>()));
                    }
                }
                return ereol::Response<std::map<std::string, ereol::Record>>(result);
            } else { return ereol::ErrorResponse::invalidInput<std::map<std::string, ereol::Record>>(); }
        } else { return ereol::ErrorResponse::genericErrorAPI<std::map<std::string, ereol::Record>>({}); }
    } else { return ereol::ErrorResponse::genericErrorHTTP<std::map<std::string, ereol::Record>>({}); }
}


#ifdef COMPILE_LUA
void ereol::luaRegisterItem(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::Item>("Item")
                /*
            .addStaticFunction ("getLibraryProfile",
                std::function<ereol::Response<ereol::LibraryProfile>(int)>(
                [](int library){
                    return ereol::Item::getLibraryProfile(static_cast<ereol::Library>(library));
                })
            )*/
            .addStaticFunction ("getOthersOfSameTitle", ereol::Item::getOthersOfSameTitle)
            .addStaticFunction ("getMoreOfSameGenre", ereol::Item::getMoreOfSameGenre)
            .addStaticFunction ("getMoreOfSameCreator", ereol::Item::getMoreOfSameCreator)
            .addStaticFunction ("getMoreInSameSeries", ereol::Item::getMoreInSameSeries)
            .addStaticFunction ("getSomethingSimilar", ereol::Item::getSomethingSimilar)
            .addStaticFunction ("getPersonalRecommendations", ereol::Item::getPersonalRecommendations)
            .addStaticFunction ("getReviews", ereol::Item::getReviews)
            .addStaticFunction ("getCoverUrls", ereol::Item::getCoverUrls)
            .addStaticFunction ("getLoanStatuses", ereol::Item::getLoanStatuses)
            .addStaticFunction ("getProduct", ereol::Item::getProduct)
            .addStaticFunction ("getRecords", ereol::Item::getRecords)
            .addStaticFunction ("search", ereol::Item::search)

        .endClass()
    .endNamespace();
}
#endif