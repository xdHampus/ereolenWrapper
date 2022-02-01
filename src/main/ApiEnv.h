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

    enum Library {
        ALBERTSLUND,
        ALLEROED,
        ASSENS,
        BALLERUP,
        BILLUND,
        BORNHOLM,
        BROENDBY,
        BROENDERSLEV,
        BYARBOKASAVNIO,
        DRAGOER,
        EGEDAL,
        ESBJERG,
        FAVRSKOV,
        FAXE,
        FREDENSBORG,
        FREDERICIA,
        FREDERIKSBERG,
        FREDERIKSHAVN,
        FREDERIKSSUND,
        FURESOE,
        FAABORG_MIDTFYN,
        GENTOFTE,
        GLADSAXE,
        GLOSTRUP,
        GREVE,
        GRIBSKOV,
        GULDBORGSUND,
        HADERSLEV,
        HALSNAES,
        HEDENSTED,
        HELSINGOER,
        HERLEV,
        HERNING,
        HILLEROED,
        HJOERRING,
        HOLBAEK,
        HOLSTEBRO,
        HORSENS,
        HVIDOVRE,
        HOEJE_TAASTRUP,
        HOERSHOLM,
        IKAST_BRANDE,
        ISHOEJ,
        JAMMERBUGT,
        KALUNDBORG,
        KALAALLIT,
        KERTEMINDE,
        KOLDING,
        KOEBENHAVN,
        KOEGE,
        LANGELAND,
        LEJRE,
        LEMVIG,
        LOLLAND,
        LYNGBY,
        LAESOE,
        MARIAGERFJORD,
        MIDDELFART,
        MORSOE,
        NORDDJURS,
        NORDFYN,
        NYBORG,
        NAESTVED,
        ODDER,
        ODENSE,
        ODSHERRED,
        RANDERS,
        REBILD,
        RINGKOEBING_SKJERN,
        RINGSTED,
        ROSKILDE,
        RUDERSDAL,
        ROEDOVRE,
        SAMSOE,
        SILKEBORG,
        SKANDERBORG,
        SKIVE,
        SLAGELSE,
        SOLROED,
        SOROE,
        STEVNS,
        STRUER,
        SVENDBORG,
        SYDDJURS,
        SYDSLESVIG,
        SOENDERBORG,
        THISTED,
        TOENDER,
        TAARNBY,
        VALLENSBAEK,
        VARDE,
        VEJEN,
        VEJLE,
        VESTHIMMERLAND,
        VIBORG,
        VORDINGBORG,
        AEROE,
        AABENRAA,
        AALBORG,
        AARHUS,
    };


    class ApiEnv {
    private:
        inline static const std::string apiKey = "HgAMJJhTM5qp9Q3nElWE0P2yPrdOoc8N";
        inline static const std::string rpcEndpoint = "https://ereolen.redia.dk/v1/rpc.php/";
        inline static const std::string appVersion = "android_3.5.3";
        inline static const std::string language = "da";
        inline static const int libCount = 100;
        inline static const std::string libNames[libCount] = {
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
        inline static const std::string libCodes[libCount] = {
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




    public:
        static std::string getApiKey() { return apiKey; }
        static std::string getRPC() { return rpcEndpoint; }
        static std::string getAppVersion() { return appVersion; }
        static std::string getLanguage() { return language; }
        static int getLibraryCount() { return libCount; }

        static std::string getLibraryName(ereol::Library library) {
            return libNames[library];
        }
        static std::string getLibraryCode(ereol::Library library) {
            return libCodes[library];
        }
        static std::optional<ereol::Library> getLibraryFromCode(std::string libraryCode){
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