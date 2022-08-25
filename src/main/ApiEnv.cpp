#include "ApiEnv.h"
#ifdef __cplusplus 
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <string>
#include <map>


const std::string ereol::ApiEnv::apiKey = "HgAMJJhTM5qp9Q3nElWE0P2yPrdOoc8N";
std::string ereol::ApiEnv::rpcEndpoint = "https://ereolen.redia.dk/v1/rpc.php/";
const std::string ereol::ApiEnv::appVersion = "android_3.5.3";
const std::string ereol::ApiEnv::language = "da";


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

extern "C" { 
    namespace ereol {
#endif
        const char*  ereol_ApiEnv_getApiKey(){
            return ereol::ApiEnv::getApiKey().c_str();
        }
        const char*  ereol_ApiEnv_getRPC(){
            return ereol::ApiEnv::getRPC().c_str();
        }
        void  ereol_ApiEnv_setRPC(char* endpoint){
            std::string str(endpoint);
            ereol::ApiEnv::setRPC(str);
        }
        const char*  ereol_ApiEnv_getAppVersion(){
            return ereol::ApiEnv::getAppVersion().c_str();
        }
        const char*  ereol_ApiEnv_getLanguage(){
            return ereol::ApiEnv::getLanguage().c_str();
        }
        int  ereol_ApiEnv_getLibraryCount(){
            return ereol::ApiEnv::getLibraryCount();
        }
        const char*  ereol_ApiEnv_getLibraryName(Library* library){
            return ereol::ApiEnv::getLibraryName(*library).c_str();
        }
        const char*  ereol_ApiEnv_getLibraryCode(Library* library){
            return ereol::ApiEnv::getLibraryCode(*library).c_str();
        }
        Library*  ereol_ApiEnv_getLibraryFromCode(char* libraryCode){
            std::string str(libraryCode);
            std::optional<Library> optLibrary = ereol::ApiEnv::getLibraryFromCode(str);
            if(optLibrary.has_value()){
                return &optLibrary.value();
            } else {
                return nullptr;
            }
        }
        const char*   ereol_ApiEnv_convertRpcPayloadToJSON(RpcPayload* rpcPayload){
            return ereol::ApiEnv::convertRpcPayloadToJSON(*rpcPayload).c_str();
        }
        const char*   ereol_ApiEnv_getRpcPayloadJSON(char* method, char** params, size_t paramsN){
            std::string sMethod(method);
            std::vector<std::string> vParams(params, params + paramsN);
            return ereol::ApiEnv::getRpcPayloadJSON(sMethod, vParams).c_str();
        }

#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 