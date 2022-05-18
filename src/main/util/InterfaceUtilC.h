#ifndef EREOLENWRAPPER_INTERFACEUTILC_H
#define EREOLENWRAPPER_INTERFACEUTILC_H
#ifdef __cplusplus
#include <vector>
#include <string> 
namespace ereol {

template<class T>
std::vector<T>* AllocateVector(std::vector<T>* v);

class VectorStrC
{
    private:
        std::vector<const char*>* m_v;
    public:
        VectorStrC(std::vector<std::string> *v);
        const char** data();
        ~VectorStrC();

};

#else
//c_str_vector
typedef struct VectorStrC VectorStrC;
void ereol_VectorStrC_delete(VectorStrC* v);   
const char** ereol_VectorStrC_getData(VectorStrC* v);   

#endif //end __cplusplus
#ifdef __cplusplus 
}
#endif //end __cplusplus

#endif //EREOLENWRAPPER_INTERFACEUTILC_H
