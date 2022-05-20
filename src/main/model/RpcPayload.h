#ifndef EREOLENWRAPPER_RPCPAYLOAD_H
#define EREOLENWRAPPER_RPCPAYLOAD_H
#include "../util/InterfaceUtilC.h"
#ifdef __cplusplus 
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
#else
//struct
typedef struct RpcPayload RpcPayload;
RpcPayload*  ereol_RpcPayload_instantiate(); 
void ereol_RpcPayload_delete(RpcPayload* m);
//jsonrpc
const char*  ereol_RpcPayload_getJsonRPC(RpcPayload* m); 
void   ereol_RpcPayload_setJsonRPC(RpcPayload* m,  const char* cp); 
//method
const char*  ereol_RpcPayload_getMethod(RpcPayload* m); 
void   ereol_RpcPayload_setMethod(RpcPayload* m,  const char* cp); 
//params
VectorStrC*  ereol_RpcPayload_getParams(RpcPayload* m); 
size_t ereol_RpcPayload_getParams_size(RpcPayload* m); 
void ereol_RpcPayload_getParams_insert(RpcPayload* m, const char* x); 
void   ereol_RpcPayload_setParams(RpcPayload* m,  const char** arr, size_t n); 
//id
const char*  ereol_RpcPayload_getId(RpcPayload* m); 
void   ereol_RpcPayload_setId(RpcPayload* m,  const char* cp); 
#endif //end __cplusplus
#ifdef __cplusplus 
}
#endif //end __cplusplus

#endif //EREOLENWRAPPER_RPCPAYLOAD_H
