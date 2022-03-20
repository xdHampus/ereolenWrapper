//
// Created by root on 1/30/22.
//

#include "ApiEnv.h"
#include <nlohmann/json.hpp>
#include <string>

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



nlohmann::json ereol::ApiEnv::convertRpcPayloadToJSON(ereol::RpcPayload rpcPayload){
    nlohmann::json j;

    j["jsonrpc"] = rpcPayload.jsonrpc;
    j["method"] = rpcPayload.method;
    j["params"] = rpcPayload.params;
    j["id"] = rpcPayload.id;

    return j;
}
std::string ereol::ApiEnv::getRpcPayloadJSON(std::string method, std::vector<std::string> params){
    ereol::RpcPayload rpcPayload;
    rpcPayload.method = method;
    rpcPayload.params = params;

    return convertRpcPayloadToJSON(rpcPayload).dump();
}
