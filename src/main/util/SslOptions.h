#ifndef EREOLENWRAPPER_SSLOPTIONS_H
#define EREOLENWRAPPER_SSLOPTIONS_H

#include <cpr/cpr.h>
#include <string>
#include <utility>

#include "src/main/ApiEnv.h"

namespace ereol {
    // libcurl has no process-wide CA setting -- CURLOPT_CAINFO is per handle and
    // cpr makes a fresh handle per request -- so every call site has to pass
    // this. Empty CA bundle means "leave the backend's default alone".
    inline cpr::SslOptions sslOptions() {
        std::string ca = ereol::ApiEnv::getCaBundle();
        if(ca.empty()) { return cpr::SslOptions{}; }
        return cpr::Ssl(cpr::ssl::CaInfo{cpr::fs::path{std::move(ca)}});
    }
}

#endif //EREOLENWRAPPER_SSLOPTIONS_H
