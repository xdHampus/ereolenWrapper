#include "InterfaceUtilC.h"

#ifdef __cplusplus 
#include <functional>
#include <cstring>
#include <algorithm>
ereol::VectorStrC::VectorStrC(std::vector<std::string> *v) {
    ereol::VectorStrC::m_v = new std::vector<const char*>; 
    std::transform(std::begin(*v), std::end(*v), std::back_inserter(*ereol::VectorStrC::m_v), std::mem_fn(&std::string::c_str));
}
const char** ereol::VectorStrC::data(){
    return ereol::VectorStrC::m_v->data();
}
ereol::VectorStrC::~VectorStrC(){
    delete ereol::VectorStrC::m_v;
}

template<class T>
std::vector<T>* AllocateVector(std::vector<T>* v){
    typename std::vector<T>* o = new std::vector<T>(v->size());
    std::swap_ranges(v->begin(), v->end(), o->begin());
    return o;
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
#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 