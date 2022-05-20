#include "RpcPayload.h"
#ifdef __cplusplus 
#include <functional>
    extern "C" { 
        namespace ereol {
#endif
            RpcPayload*  ereol_RpcPayload_instantiate() 
            {
                return new RpcPayload();
            }
            void ereol_RpcPayload_delete(RpcPayload* m)
            { 
                delete m;
            } 
            
            const char*  ereol_RpcPayload_getJsonRPC(RpcPayload* m) 
            { return m->jsonrpc.c_str(); } 
            void   ereol_RpcPayload_setJsonRPC(RpcPayload* m,  const char* cp) 
            { m->jsonrpc.assign(cp); }    
            const char*  ereol_RpcPayload_getMethod(RpcPayload* m) 
            { return m->method.c_str(); } 
            void   ereol_RpcPayload_setMethod(RpcPayload* m,  const char* cp) 
            { m->method.assign(cp); }    
            VectorStrC* ereol_RpcPayload_getParams(RpcPayload* m) 
            { 
                return new VectorStrC(&m->params);
            } 
            size_t ereol_RpcPayload_getParams_size(RpcPayload* m) 
            { return m->params.size();} 
            void ereol_RpcPayload_getParams_insert(RpcPayload* m, const char* x) 
            { 
                std::string str(x);
                m->params.push_back(str); 
            } 
            void   ereol_RpcPayload_setParams(RpcPayload* m,  const char** arr, size_t n) 
            {  
                m->params = std::vector<std::string>(arr, arr + n); 
            } 
            const char*  ereol_RpcPayload_getId(RpcPayload* m) 
            { return m->id.c_str(); } 
            void   ereol_RpcPayload_setId(RpcPayload* m, const  char* cp) 
            { m->id.assign(cp); }                  
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 