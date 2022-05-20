#include "InterfaceUtilC.h"

#ifdef __cplusplus 
#include <functional>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
ereol::VectorStrC::VectorStrC(std::vector<std::string> *v) {
    ereol::VectorStrC::m_v = new std::vector<const char*>; 
    std::transform(std::begin(*v), std::end(*v), std::back_inserter(*ereol::VectorStrC::m_v), std::mem_fn(&std::string::c_str));
}
const char** ereol::VectorStrC::data(){
    return ereol::VectorStrC::m_v->data();
}
size_t ereol::VectorStrC::size(){
    return ereol::VectorStrC::m_v->size();
}
ereol::VectorStrC::~VectorStrC(){
    delete ereol::VectorStrC::m_v;
}

ereol::VectorVoid::VectorVoid(std::vector<void*> *v) {
    ereol::VectorVoid::m_v = v;
}
size_t ereol::VectorVoid::size(){
    return ereol::VectorVoid::m_v->size();
}
void** ereol::VectorVoid::data(){
    return ereol::VectorVoid::m_v->data();
}
void ereol::VectorVoid::clear(){
    return ereol::VectorVoid::m_v->clear();
}
ereol::VectorVoid::~VectorVoid(){
    delete ereol::VectorVoid::m_v;
}

              

#else
#endif
#ifdef __cplusplus 
extern "C" { 
    namespace ereol {
#endif
        void  ereol_VectorStrC_delete(VectorStrC* v)
        { delete v; }
        const char**  ereol_VectorStrC_getData(VectorStrC* v) 
        { return v->data(); } 
        size_t  ereol_VectorStrC_size(VectorStrC* v) 
        { return v->size(); } 

        void  ereol_VectorVoid_delete(VectorVoid* v)
        { delete v; }        
        void  ereol_VectorVoid_clear(VectorVoid* v)
        { v->clear(); }
        void**  ereol_VectorVoid_getData(VectorVoid* v) 
        { return v->data(); } 
        size_t  ereol_VectorVoid_size(VectorVoid* v) 
        { return v->size(); }         

#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 