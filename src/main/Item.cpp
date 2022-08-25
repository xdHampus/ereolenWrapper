#include "Item.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "ApiEnv.h"
#include "util/JSONHelper.h"
#include "util/ApiCaller.h"

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

std::vector<ereol::Record> ereol::Item::getOthersOfSameTitle(std::string identifier, ereol::Token token){
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            otherTypesOfSameTitleMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    identifier
            }
    );

    cpr::Response r = cpr::Post(
            cpr::Url{ereol::ApiEnv::getRPC()},
            cpr::Body{payloadJson},
            cpr::Header{{"Content-Type", "text/plain"}},
            cpr::Cookies{{"PHPSESSID", token.sessid}});


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
                return results;
            } else { //TODO: Invalid input or no result
            }
        } else { //TODO: Handle API errors
        }
    } else { //TODO: Handle HTTP errors
    }
    return {};
}

ereol::PageResult ereol::Item::getMoreOfSameGenre(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            moreOfSameGenreMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    identifier
            },
            settings
    );
    ereol::Response<ereol::PageResult> response = ereol::ApiCaller::getResponse<ereol::PageResult>(payloadJson, token);
    return response.data;
}

ereol::PageResult
ereol::Item::getMoreOfSameCreator(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            moreOfSameCreatorMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    identifier
            },
            settings
    );
    ereol::Response<ereol::PageResult> response = ereol::ApiCaller::getResponse<ereol::PageResult>(payloadJson, token);
    return response.data;
}

ereol::PageResult ereol::Item::getMoreInSameSeries(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            moreInSameSeriesMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    identifier
            },
            settings
    );
    ereol::Response<ereol::PageResult> response = ereol::ApiCaller::getResponse<ereol::PageResult>(payloadJson, token);
    return response.data;
}

std::vector<ereol::Record> ereol::Item::getSomethingSimilar(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            somethingSimilarMethod,
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
}
//TODO: Not implemented correctly
std::vector<ereol::Record> ereol::Item::getPersonalRecommendations(std::string identifier, ereol::Token token, ereol::QuerySettings settings) {
    return {};
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

std::vector<ereol::Review> ereol::Item::getReviews(std::string identifier, ereol::Token token) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            reviewsMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    identifier
            }
    );
    ereol::Response<std::vector<ereol::Review>> response = ereol::ApiCaller::getResponse<std::vector<ereol::Review>>(payloadJson, token);
    return response.data;
}


std::map<std::string, std::string> ereol::Item::getCoverUrls(std::vector<std::string> identifiers, ereol::Token token) {
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
    jr = ereol::ApiCaller::getResponse(payloadJson, token);

    std::map<std::string, std::string> result;
    if(jr["result"] != nullptr && jr["result"]["result"] != nullptr) {
        if (jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
            for (const auto& item : jr["result"]["data"].items())
            {
                if(item.value()["result"] != nullptr &&
                   item.value()["result"].get<bool>() &&
                   item.value()["data"] != nullptr &&
                   item.value()["data"]["url"] != nullptr){
                    result.insert(std::pair<std::string, std::string>(item.key(), item.value()["data"]["url"].get<std::string>()));
                }
            }
        }
    }
    return result;
}

std::map<std::string, std::string>
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
    jr = ereol::ApiCaller::getResponse(payloadJson, token);

    std::map<std::string, std::string> result;
    if(jr["result"] != nullptr && jr["result"]["result"] != nullptr) {
        if (jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
            for (const auto& item : jr["result"]["data"].items())
            {
                if(item.value()["result"] != nullptr &&
                   item.value()["result"].get<bool>() &&
                   item.value()["data"] != nullptr &&
                   item.value()["data"]["loanStatus"] != nullptr){
                    result.insert(std::pair<std::string, std::string>(item.key(), item.value()["data"]["loanStatus"].get<std::string>()));
                }
            }
        }
    }
    return result;
}

ereol::Record ereol::Item::getProduct(std::string identifier, ereol::Token token) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            productMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    identifier
            }
    );
    ereol::Response<ereol::Record> response = ereol::ApiCaller::getResponse<ereol::Record>(payloadJson, token);
    return response.data;
}

ereol::PageResult ereol::Item::search(std::string queryString, ereol::Token token, ereol::QuerySettings settings) {
    std::string payloadJson = ereol::ApiEnv::getRpcPayloadJSON(
            searchMethod,
            {
                    ereol::ApiEnv::getApiKey(),
                    ereol::ApiEnv::getAppVersion(),
                    ereol::ApiEnv::getLanguage(),
                    ereol::ApiEnv::getLibraryCode(token.library),
                    queryString
            },
            settings
    );
    ereol::Response<ereol::PageResult> response = ereol::ApiCaller::getResponse<ereol::PageResult>(payloadJson, token);
    return response.data;
}

std::map<std::string, ereol::Record> ereol::Item::getRecords(std::vector<std::string> identifiers, ereol::Token token) {
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
    jr = ereol::ApiCaller::getResponse(payloadJson, token);

    std::map<std::string, ereol::Record> result;
    if(jr["result"] != nullptr && jr["result"]["result"] != nullptr) {
        if (jr["result"]["result"].get<bool>() && jr["result"]["data"] != nullptr) {
            for (const auto& item : jr["result"]["data"].items())
            {
                if(item.value()["result"] != nullptr &&
                   item.value()["result"].get<bool>() &&
                   item.value()["data"] != nullptr){
                    result.insert(std::pair<std::string, ereol::Record>(item.key(), item.value()["data"].get<ereol::Record>()));
                }
            }
        }
    }
    return result;
}