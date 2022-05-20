
#ifndef EREOLENWRAPPER_PRODUCT_H
#define EREOLENWRAPPER_PRODUCT_H

#include "Contributor.h"
#include "LoanIdentifier.h"
#ifdef __cplusplus 
#include <optional>
#include <string>
#include <vector>

namespace ereol {
    struct Product {
        ereol::LoanIdentifier loanIdentifier;  
        std::string title;
        std::string publisher;
        std::string description;
        std::string language;
        std::string mediaType;

        std::optional<uint64_t> createdDate;
        std::optional<uint64_t> updatedDate;
        std::optional<uint64_t> firstPublished;
        std::optional<uint64_t> duration;    

        std::optional<std::string> productType;
        std::optional<std::string> cover;
        std::optional<std::string> phid;
        std::optional<std::string> format;
        std::optional<std::string> thumbnail;
        std::optional<std::string> abstract;
        std::optional<std::string> year;
        std::optional<std::string> edition;
        std::optional<std::string> shelfmark;
        std::optional<std::string> seriesPart;
        std::optional<std::string> subscription;
        std::optional<std::string> eReolenGlobalUrl;

        std::optional<std::vector<ereol::Contributor>> contributors;

        std::optional<std::vector<std::string>> creators;
        std::optional<std::vector<std::string>> series;
        std::optional<std::vector<std::string>> subjects;
        std::optional<std::vector<std::string>> types;
    };

    void from_json(const std::string  &s, ereol::Product& x);
    void to_json(std::string & s, const ereol::Product & x);
#else
//struct
typedef struct Product Product;
Product*  ereol_Product_instantiate(); 
void ereol_Product_delete(Product* m);   

//loanIdentifier
LoanIdentifier*  ereol_Product_getLoanIdentifier(Product* m); 
void   ereol_Product_setLoanIdentifier(Product* m,  LoanIdentifier* identifier); 
//title
const char*  ereol_Product_getTitle(Product* m); 
void   ereol_Product_setTitle(Product* m, const char* cp); 
//publisher
const char*  ereol_Product_getPublisher(Product* m); 
void   ereol_Product_setPublisher(Product* m, const char* cp); 
//description
const char*  ereol_Product_getDescription(Product* m); 
void   ereol_Product_setDescription(Product* m, const char* cp); 
//language
const char*  ereol_Product_getLanguage(Product* m); 
void   ereol_Product_setLanguage(Product* m, const char* cp); 
//mediaType
const char*  ereol_Product_getMediaType(Product* m); 
void   ereol_Product_setMediaType(Product* m, const char* cp); 


//createdDate
uint64_t  ereol_Product_getCreatedDate(Product* m); 
void   ereol_Product_setCreatedDate(Product* m,  uint64_t unixTime); 
//updatedDate
uint64_t  ereol_Product_getUpdatedDate(Product* m); 
void   ereol_Product_setUpdatedDate(Product* m,  uint64_t unixTime); 
//firstPublished
uint64_t  ereol_Product_getFirstPublished(Product* m); 
void   ereol_Product_setFirstPublished(Product* m,  uint64_t unixTime); 
//duration
uint64_t  ereol_Product_getDuration(Product* m); 
void   ereol_Product_setDuration(Product* m,  uint64_t unixTime); 

//productType
const char*  ereol_Product_getProductType(Product* m); 
void   ereol_Product_setProductType(Product* m, const char* cp); 
//cover
const char*  ereol_Product_getCover(Product* m); 
void   ereol_Product_setCover(Product* m, const char* cp); 
//phid
const char*  ereol_Product_getPhid(Product* m); 
void   ereol_Product_setPhid(Product* m, const char* cp); 
//format
const char*  ereol_Product_getFormat(Product* m); 
void   ereol_Product_setFormat(Product* m, const char* cp); 
//thumbnail
const char*  ereol_Product_getThumbnail(Product* m); 
void   ereol_Product_setThumbnail(Product* m, const char* cp); 
//abstract
const char*  ereol_Product_getAbstract(Product* m); 
void   ereol_Product_setAbstract(Product* m, const char* cp); 
//year
const char*  ereol_Product_getYear(Product* m); 
void   ereol_Product_setYear(Product* m, const char* cp); 
//edition
const char*  ereol_Product_getEdition(Product* m); 
void   ereol_Product_setEdition(Product* m, const char* cp); 
//shelfmark
const char*  ereol_Product_getShelfmark(Product* m); 
void   ereol_Product_setShelfmark(Product* m, const char* cp); 
//seriesPart
const char*  ereol_Product_getSeriesPart(Product* m); 
void   ereol_Product_setSeriesPart(Product* m, const char* cp); 
//subscription
const char*  ereol_Product_getSubscription(Product* m); 
void   ereol_Product_setSubscription(Product* m, const char* cp); 
//eReolenGlobalUrl
const char*  ereol_Product_getEReolenGlobalUrl(Product* m); 
void   ereol_Product_setEReolenGlobalUrl(Product* m, const char* cp); 

//contributors
VectorVoid* ereol_Product_getContributors(Product* m); 
size_t ereol_Product_getContributors_size(Product* m); 
void ereol_Product_getContributors_insert(Product* m, const Contributor* x); 
void ereol_Product_setContributors(Product* m, const  Contributor** arr, size_t n);    


//creators
VectorStrC*  ereol_Product_getCreators(Product* m); 
size_t ereol_Product_getCreators_size(Product* m); 
void ereol_Product_getCreators_insert(Product* m, const char* x); 
void   ereol_Product_setCreators(Product* m, const  char** arr, size_t n);    
//series
VectorStrC*  ereol_Product_getSeries(Product* m); 
size_t ereol_Product_getSeries_size(Product* m); 
void ereol_Product_getSeries_insert(Product* m, const char* x); 
void   ereol_Product_setSeries(Product* m, const  char** arr, size_t n);    
//subjects
VectorStrC*  ereol_Product_getSubjects(Product* m); 
size_t ereol_Product_getSubjects_size(Product* m); 
void ereol_Product_getSubjects_insert(Product* m, const char* x); 
void   ereol_Product_setSubjects(Product* m, const  char** arr, size_t n);    
//types
VectorStrC*  ereol_Product_getTypes(Product* m); 
size_t ereol_Product_getTypes_size(Product* m); 
void ereol_Product_getTypes_insert(Product* m, const char* x); 
void   ereol_Product_setTypes(Product* m, const  char** arr, size_t n);    

#endif
#ifdef __cplusplus 
}
#endif

#endif //EREOLENWRAPPER_PRODUCT_H
