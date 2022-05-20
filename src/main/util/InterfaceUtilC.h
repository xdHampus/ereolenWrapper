#ifndef EREOLENWRAPPER_INTERFACEUTILC_H
#define EREOLENWRAPPER_INTERFACEUTILC_H
#ifdef __cplusplus
#include <vector>
#include <string> 
namespace ereol {


class VectorStrC
{
    private:
        std::vector<const char*>* m_v;
    public:
        VectorStrC(std::vector<std::string> *v);
        const char** data();
        size_t size();
        ~VectorStrC();

};

class VectorVoid
{
    private:
        std::vector<void*>* m_v;
    public:
        template<typename T, typename A>
        VectorVoid(std::vector<T, A> &v) {
            ereol::VectorVoid::m_v = new std::vector<void*>();
            ereol::VectorVoid::m_v->reserve(v.size());
            int i;
            for(i = 0; i < v.size(); i++){
                T* t = &v[i];
                ereol::VectorVoid::m_v->push_back((void*)t);
            }
        };
        VectorVoid(std::vector<void*> *v);
        void** data();
        void clear();
        size_t size();
        ~VectorVoid();
};



#else
//c_str_vector
typedef struct VectorStrC VectorStrC;
void ereol_VectorStrC_delete(VectorStrC* v);
size_t ereol_VectorStrC_size(VectorStrC* v);   
const char** ereol_VectorStrC_getData(VectorStrC* v);   
//vectorvoid
typedef struct VectorVoid VectorVoid;
void ereol_VectorVoid_delete(VectorVoid* v);
void ereol_VectorVoid_clear(VectorVoid* v);
size_t ereol_VectorVoid_size(VectorVoid* v);   
void** ereol_VectorVoid_getData(VectorVoid* v);   

#endif //end __cplusplus
#ifdef __cplusplus 
}
#endif //end __cplusplus

#endif //EREOLENWRAPPER_INTERFACEUTILC_H
