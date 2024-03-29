#include "ApiEnv.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <string>
#include <map>
#ifdef COMPILE_LUA
#include "lua/LuaInterface.h"
#include "lua/ResponseLua.h"
#endif

const std::string apiKey = "HgAMJJhTM5qp9Q3nElWE0P2yPrdOoc8N";
static std::string rpcEndpoint = "https://ereolen.redia.dk/v1/rpc.php/";
const std::string appVersion = "android_3.5.3";
const std::string language = "da";

std::string ereol::ApiEnv::getApiKey(){
    return apiKey;
}
std::string ereol::ApiEnv::getRPC(){
    return rpcEndpoint;
}
void ereol::ApiEnv::setRPC(std::string endpoint){
    rpcEndpoint = std::move(endpoint);
}
std::string ereol::ApiEnv::getAppVersion(){
    return appVersion;
}
std::string ereol::ApiEnv::getLanguage(){
    return language;
}


const int libCount = 100;
static const std::string libNames[libCount] = {
        "Albertslund",
        "Allerød",
        "Assens",
        "Ballerup",
        "Billund",
        "Bornholm",
        "Brøndby",
        "Brønderslev",
        "Býarbókasavnið",
        "Dragør",
        "Egedal",
        "Esbjerg",
        "Favrskov",
        "Faxe",
        "Fredensborg",
        "Fredericia",
        "Frederiksberg",
        "Frederikshavn",
        "Frederikssund",
        "Furesø",
        "Faaborg-Midtfyn",
        "Gentofte",
        "Gladsaxe",
        "Glostrup",
        "Greve",
        "Gribskov",
        "Guldborgsund",
        "Haderslev",
        "Halsnæs",
        "Hedensted",
        "Helsingør",
        "Herlev",
        "Herning",
        "Hillerød",
        "Hjørring",
        "Holbæk",
        "Holstebro",
        "Horsens",
        "Hvidovre",
        "Høje-Taastrup",
        "Hørsholm",
        "Ikast-Brande",
        "Ishøj",
        "Jammerbugt",
        "Kalundborg",
        "Kalaallit Nunaat/Grønland",
        "Kerteminde",
        "Kolding",
        "København",
        "Køge",
        "Langeland",
        "Lejre",
        "Lemvig",
        "Lolland",
        "Lyngby",
        "Læsø",
        "Mariagerfjord",
        "Middelfart",
        "Morsø",
        "Norddjurs",
        "Nordfyn",
        "Nyborg",
        "Næstved",
        "Odder",
        "Odense",
        "Odsherred",
        "Randers",
        "Rebild",
        "Ringkøbing-Skjern",
        "Ringsted",
        "Roskilde",
        "Rudersdal",
        "Rødovre",
        "Samsø",
        "Silkeborg",
        "Skanderborg",
        "Skive",
        "Slagelse",
        "Solrød",
        "Sorø",
        "Stevns",
        "Struer",
        "Svendborg",
        "Syddjurs",
        "Sydslesvig",
        "Sønderborg",
        "Thisted",
        "Tønder",
        "Tårnby",
        "Vallensbæk",
        "Varde",
        "Vejen",
        "Vejle",
        "Vesthimmerland",
        "Viborg",
        "Vordingborg",
        "Ærø",
        "Aabenraa",
        "Aalborg",
        "Aarhus"
};
static const std::string libCodes[libCount] = {
        "albertslundbib",
        "alleroedbib",
        "assensbib",
        "ballerupbib",
        "billundbib",
        "bornholmsbib",
        "broendbybib",
        "broenderslevbib",
        "byarbokasavniobib",
        "dragoerbib",
        "egedalbib",
        "esbjergbib",
        "favrskovbib",
        "faxebib",
        "fredensborgbib",
        "fredericiabib",
        "frederiksbergbib",
        "frederikshavnbib",
        "frederikssundbib",
        "faaborgmidtfynbib",
        "furesoebib",
        "gentoftebib",
        "gladsaxebib",
        "glostrupbib",
        "grevebib",
        "gribskovbib",
        "guldborgsundbib",
        "haderslevbib",
        "halsnaesbib",
        "hedenstedbib",
        "helsingoerbib",
        "herlevbib",
        "herningbib",
        "hilleroedbib",
        "hjoerringbib",
        "holbaekbib",
        "holstebrobib",
        "horsensbib",
        "hvidovrebib",
        "hoejetaastrupbib",
        "hoersholmbib",
        "ikastbrandebib",
        "ishoejbib",
        "jammerbugtbib",
        "kalundborgbib",
        "kalaallitbib",
        "kertemindebib",
        "koldingbib",
        "koebenhavnsbib",
        "koegebib",
        "langelandbib",
        "lejrebib",
        "lemvigbib",
        "lollandbib",
        "lyngbybib",
        "laesoebib",
        "mariagerfjordbib",
        "middelfartbib",
        "morsoebib",
        "norddjursbib",
        "nordfynbib",
        "nyborgbib",
        "naestvedbib",
        "odderbib",
        "odensebib",
        "odsherredbib",
        "randersbib",
        "rebildbib",
        "ringkoebingskjernbib",
        "ringstedbib",
        "roskildebib",
        "rudersdalbib",
        "roedovrebib",
        "samsoebib",
        "silkeborgbib",
        "skanderborgbib",
        "skivebib",
        "slagelsebib",
        "solroedbib",
        "soroebib",
        "stevnsbib",
        "struerbib",
        "svendborgbib",
        "syddjursbib",
        "sydslesvigbib",
        "soendborgbib",
        "thistedbib",
        "toenderbib",
        "taarnbybib",
        "vallensbaekbib",
        "vardebib",
        "vejenbib",
        "vejlebib",
        "vesthimmerlandbib",
        "viborgbib",
        "vordingborgbib",
        "aeroebib",
        "aabenraabib",
        "aalborgbib",
        "aarhusbib"
};



int ereol::ApiEnv::getLibraryCount() { return libCount; }
std::string ereol::ApiEnv::getLibraryName(ereol::Library library) {
    return libNames[library];
}
std::string ereol::ApiEnv::getLibraryCode(ereol::Library library) {
    return libCodes[library];
}

std::optional<ereol::Library> ereol::ApiEnv::getLibraryFromCode(std::string libraryCode){
    long libIndex = std::distance(libCodes,
                                  std::find(
                                          libCodes,
                                          libCodes + libCount,
                                          libraryCode));

    if(libIndex > 0 && libIndex < libCount){
        return {static_cast<ereol::Library>(libIndex)};
    }
    return {};
}



std::string ereol::ApiEnv::convertRpcPayloadToJSON(ereol::RpcPayload rpcPayload){
    nlohmann::json j;

    j["jsonrpc"] = rpcPayload.jsonrpc;
    j["method"] = rpcPayload.method;
    j["params"] = rpcPayload.params;
    j["id"] = rpcPayload.id;

    return j.dump();
}
std::string ereol::ApiEnv::getRpcPayloadJSON(std::string method, std::vector<std::string> params){
    ereol::RpcPayload rpcPayload;
    rpcPayload.method = method;
    rpcPayload.params = params;
    return convertRpcPayloadToJSON(rpcPayload);
}

std::string ereol::ApiEnv::convertRpcPayloadToJSON(ereol::RpcPayload rpcPayload, ereol::QuerySettings settings){
    nlohmann::json j;

    j["jsonrpc"] = rpcPayload.jsonrpc;
    j["method"] = rpcPayload.method;
    j["params"] = rpcPayload.params;
    j["id"] = rpcPayload.id;

    j["params"][5] = settings.startIndex;
    j["params"][6] = settings.endIndex;
    if(settings.facets.has_value()){
        j["params"][7] = settings.facets.value();
    }
    std::string wtf = j.dump();
    std::string lmao = wtf;

    return lmao;
}
std::string ereol::ApiEnv::getRpcPayloadJSON(std::string method, std::vector<std::string> params, ereol::QuerySettings settings){
    ereol::RpcPayload rpcPayload;
    rpcPayload.method = method;
    rpcPayload.params = params;

    return convertRpcPayloadToJSON(rpcPayload, settings);
}

#ifdef COMPILE_LUA
void ereol::luaRegisterApiEnv(lua_State* L){
    luabridge::getGlobalNamespace(L)
    .beginNamespace("ereol")
        .beginClass<ereol::ApiEnv>("ApiEnv")
            .addStaticFunction ("getApiKey", ereol::ApiEnv::getApiKey)
            .addStaticFunction ("getRPC", ereol::ApiEnv::getRPC)
            .addStaticFunction ("setRPC", ereol::ApiEnv::setRPC)
            .addStaticFunction ("getAppVersion", ereol::ApiEnv::getAppVersion)
            .addStaticFunction ("getLanguage", ereol::ApiEnv::getLanguage)
            .addStaticFunction ("getLibraryCount", ereol::ApiEnv::getLibraryCount)
            .addStaticFunction ("getLibraryName", std::function<std::string(int)>(
                [](int library){
                    return ereol::ApiEnv::getLibraryName(static_cast<ereol::Library>(library));
                })
            )
            .addStaticFunction ("getLibraryCode", std::function<std::string(int)>(
                [](int library){
                    return ereol::ApiEnv::getLibraryCode(static_cast<ereol::Library>(library));
                })
            )
            //TODO: Return error or optional in case of incorrect code
            .addStaticFunction ("getLibraryFromCode", std::function<int(std::string)>(
                [](std::string libraryCode){
                    auto libraryOpt = ereol::ApiEnv::getLibraryFromCode(libraryCode);
                    return libraryOpt.has_value() ? static_cast<int>(*libraryOpt) : 0;
                })
            )
            .addStaticFunction ("convertRpcPayloadToJSON", std::function<std::string(ereol::RpcPayload)>(
                [](ereol::RpcPayload p){ return ereol::ApiEnv::convertRpcPayloadToJSON(p);
            }))
            .addStaticFunction ("convertRpcPayloadToJSONSettings", std::function<std::string(ereol::RpcPayload,ereol::QuerySettings)>(
                [](ereol::RpcPayload p, ereol::QuerySettings s){ return ereol::ApiEnv::convertRpcPayloadToJSON(p,s);
            }))
            .addStaticFunction ("getRpcPayloadJSON", std::function<std::string(std::string,std::vector<std::string>)>(
                [](std::string m, std::vector<std::string> v){ return ereol::ApiEnv::getRpcPayloadJSON(m,v);
            }))
            .addStaticFunction ("getRpcPayloadJSONSettings", std::function<std::string(std::string,std::vector<std::string>,ereol::QuerySettings)>(
                [](std::string m, std::vector<std::string> v, ereol::QuerySettings s){ return ereol::ApiEnv::getRpcPayloadJSON(m,v,s);
            }))
        .endClass()
    .endNamespace();
}
#endif
