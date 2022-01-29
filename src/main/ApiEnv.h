//
// Created by root on 1/29/22.
//

#ifndef EREOLENWRAPPER_APIENV_H
#define EREOLENWRAPPER_APIENV_H

#include <string>

namespace ereol {
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
    };
}

#endif //EREOLENWRAPPER_APIENV_H
