#ifndef EREOLENWRAPPER_RPCPAYLOAD_H
#define EREOLENWRAPPER_RPCPAYLOAD_H
#include <vector>
#include <string>
namespace ereol {
    struct RpcPayload {
        std::string jsonrpc = "2.0";
        std::string method;
        std::vector<std::string> params;
        std::string id = "bf808188-c534-3369-3f00-5d8c1a389ccd";
    };
    void from_json(const std::string  &s, ereol::RpcPayload& x);
    void to_json(std::string & s, const ereol::RpcPayload & x);    

}
#endif //EREOLENWRAPPER_RPCPAYLOAD_H
