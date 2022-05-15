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
                m->~RpcPayload();  
            } 
            
            const char*  ereol_RpcPayload_getJsonRPC(RpcPayload* m) 
            { return m->jsonrpc.c_str(); } 
            void   ereol_RpcPayload_setJsonRPC(RpcPayload* m,  char* cp) 
            { m->jsonrpc.assign(cp); }    
            const char*  ereol_RpcPayload_getMethod(RpcPayload* m) 
            { return m->method.c_str(); } 
            void   ereol_RpcPayload_setMethod(RpcPayload* m,  char* cp) 
            { m->method.assign(cp); }    
            const char**  ereol_RpcPayload_getParams(RpcPayload* m) 
            { 
                std::vector<const char*> c_strs;
                std::transform(std::begin(m->params), std::end(m->params), std::back_inserter(c_strs), std::mem_fn(&std::string::c_str));
                return c_strs.data(); 
            } 
            size_t ereol_RpcPayload_getParams_size(RpcPayload* m) 
            { return m->params.size();} 
            void ereol_RpcPayload_getParams_insert(RpcPayload* m, char* x) 
            { 
                std::string str(x);
                m->params.push_back(str); 
            } 
            void   ereol_RpcPayload_setParams(RpcPayload* m,  char** arr, size_t n) 
            {  
                m->params = std::vector<std::string>(arr, arr + n); 
            } 
            const char*  ereol_RpcPayload_getId(RpcPayload* m) 
            { return m->id.c_str(); } 
            void   ereol_RpcPayload_setId(RpcPayload* m,  char* cp) 
            { m->id.assign(cp); }                  
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 