#ifndef EREOLENWRAPPER_CONTRIBUTOR_H
#define EREOLENWRAPPER_CONTRIBUTOR_H

#ifdef __cplusplus 
#include <string>
namespace ereol {
    struct Contributor {
        std::string type;
        std::string composedName;
        std::string firstName;
        std::string lastName;
    };
#else
/*struct
typedef struct Contributor Contributor;
Contributor*  ereol_Contributor_instantiate(); 
void ereol_Contributor_delete(Contributor* m);      
*/
#endif
#ifdef __cplusplus 
}
#endif

#endif //EREOLENWRAPPER_CONTRIBUTOR_H
