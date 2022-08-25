
#ifndef EREOLENWRAPPER_RECORD_H
#define EREOLENWRAPPER_RECORD_H

#include "Contributor.h"
#include "LoanIdentifier.h"
#ifdef __cplusplus 
#include <optional>
#include <string>
#include <vector>

namespace ereol {
    struct Record {
        ereol::LoanIdentifier loanIdentifier;  
        std::string title;
        std::string publisher;
        std::string description;
        std::string language;
        std::string mediaType;

        std::optional<int64_t> createdDate;
        std::optional<int64_t> updatedDate;
        std::optional<int64_t> firstPublished;
        std::optional<int64_t> duration;    

        std::optional<std::string> recordType;
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

    void from_json(const std::string  &s, ereol::Record& x);
    void to_json(std::string & s, const ereol::Record & x);
#else
//struct
typedef struct Record Record;
Record*  ereol_Record_instantiate(); 
void ereol_Record_delete(Record* m);   

//loanIdentifier
LoanIdentifier*  ereol_Record_getLoanIdentifier(Record* m); 
void   ereol_Record_setLoanIdentifier(Record* m,  LoanIdentifier* identifier); 
//title
const char*  ereol_Record_getTitle(Record* m); 
void   ereol_Record_setTitle(Record* m, const char* cp); 
//publisher
const char*  ereol_Record_getPublisher(Record* m); 
void   ereol_Record_setPublisher(Record* m, const char* cp); 
//description
const char*  ereol_Record_getDescription(Record* m); 
void   ereol_Record_setDescription(Record* m, const char* cp); 
//language
const char*  ereol_Record_getLanguage(Record* m); 
void   ereol_Record_setLanguage(Record* m, const char* cp); 
//mediaType
const char*  ereol_Record_getMediaType(Record* m); 
void   ereol_Record_setMediaType(Record* m, const char* cp); 


//createdDate
int64_t  ereol_Record_getCreatedDate(Record* m); 
void   ereol_Record_setCreatedDate(Record* m,  int64_t unixTime); 
//updatedDate
int64_t  ereol_Record_getUpdatedDate(Record* m); 
void   ereol_Record_setUpdatedDate(Record* m,  int64_t unixTime); 
//firstPublished
int64_t  ereol_Record_getFirstPublished(Record* m); 
void   ereol_Record_setFirstPublished(Record* m,  int64_t unixTime); 
//duration
int64_t  ereol_Record_getDuration(Record* m); 
void   ereol_Record_setDuration(Record* m,  int64_t unixTime); 

//recordType
const char*  ereol_Record_getRecordType(Record* m); 
void   ereol_Record_setRecordType(Record* m, const char* cp); 
//cover
const char*  ereol_Record_getCover(Record* m); 
void   ereol_Record_setCover(Record* m, const char* cp); 
//phid
const char*  ereol_Record_getPhid(Record* m); 
void   ereol_Record_setPhid(Record* m, const char* cp); 
//format
const char*  ereol_Record_getFormat(Record* m); 
void   ereol_Record_setFormat(Record* m, const char* cp); 
//thumbnail
const char*  ereol_Record_getThumbnail(Record* m); 
void   ereol_Record_setThumbnail(Record* m, const char* cp); 
//abstract
const char*  ereol_Record_getAbstract(Record* m); 
void   ereol_Record_setAbstract(Record* m, const char* cp); 
//year
const char*  ereol_Record_getYear(Record* m); 
void   ereol_Record_setYear(Record* m, const char* cp); 
//edition
const char*  ereol_Record_getEdition(Record* m); 
void   ereol_Record_setEdition(Record* m, const char* cp); 
//shelfmark
const char*  ereol_Record_getShelfmark(Record* m); 
void   ereol_Record_setShelfmark(Record* m, const char* cp); 
//seriesPart
const char*  ereol_Record_getSeriesPart(Record* m); 
void   ereol_Record_setSeriesPart(Record* m, const char* cp); 
//subscription
const char*  ereol_Record_getSubscription(Record* m); 
void   ereol_Record_setSubscription(Record* m, const char* cp); 
//eReolenGlobalUrl
const char*  ereol_Record_getEReolenGlobalUrl(Record* m); 
void   ereol_Record_setEReolenGlobalUrl(Record* m, const char* cp); 

//contributors
VectorVoid* ereol_Record_getContributors(Record* m); 
size_t ereol_Record_getContributors_size(Record* m); 
void ereol_Record_getContributors_insert(Record* m, const Contributor* x); 
void ereol_Record_setContributors(Record* m, const  Contributor** arr, size_t n);    


//creators
VectorStrC*  ereol_Record_getCreators(Record* m); 
size_t ereol_Record_getCreators_size(Record* m); 
void ereol_Record_getCreators_insert(Record* m, const char* x); 
void   ereol_Record_setCreators(Record* m, const  char** arr, size_t n);    
//series
VectorStrC*  ereol_Record_getSeries(Record* m); 
size_t ereol_Record_getSeries_size(Record* m); 
void ereol_Record_getSeries_insert(Record* m, const char* x); 
void   ereol_Record_setSeries(Record* m, const  char** arr, size_t n);    
//subjects
VectorStrC*  ereol_Record_getSubjects(Record* m); 
size_t ereol_Record_getSubjects_size(Record* m); 
void ereol_Record_getSubjects_insert(Record* m, const char* x); 
void   ereol_Record_setSubjects(Record* m, const  char** arr, size_t n);    
//types
VectorStrC*  ereol_Record_getTypes(Record* m); 
size_t ereol_Record_getTypes_size(Record* m); 
void ereol_Record_getTypes_insert(Record* m, const char* x); 
void   ereol_Record_setTypes(Record* m, const  char** arr, size_t n);    

#endif
#ifdef __cplusplus 
}
#endif

#endif //EREOLENWRAPPER_RECORD_H
