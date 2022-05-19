#include "Product.h"
#ifdef __cplusplus 
#include <functional>
#include <cstring>
#include <cstdlib>
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::Product& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Product & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::Product& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();        
        x.title = j.at("title").get<std::string>();
        x.publisher = j.at("publisher").get<std::string>();
        x.description = j.at("description").get<std::string>();
        x.language = j.at("language").get<std::string>();
        x.mediaType = j.at("mediaType").get<std::string>();

        x.createdDate = ereol::get_optional<uint64_t>(j, "createdDate");
        x.updatedDate = ereol::get_optional<uint64_t>(j, "updatedDate");
        x.firstPublished = ereol::get_optional<uint64_t>(j, "firstPublished");
        x.duration = ereol::get_optional<uint64_t>(j, "duration");

        x.productType = ereol::get_optional<std::string>(j, "icon");
        x.cover = ereol::get_optional<std::string>(j, "cover");
        x.phid = ereol::get_optional<std::string>(j, "phid");
        x.format = ereol::get_optional<std::string>(j, "format");
        x.thumbnail = ereol::get_optional<std::string>(j, "thumbnail");
        x.abstract = ereol::get_optional<std::string>(j, "abstract");
        x.year = ereol::get_optional<std::string>(j, "year");
        x.edition = ereol::get_optional<std::string>(j, "edition");
        x.shelfmark = ereol::get_optional<std::string>(j, "shelfmark");
        x.seriesPart = ereol::get_optional<std::string>(j, "seriesPart");
        x.subscription = ereol::get_optional<std::string>(j, "subscription");
        x.eReolenGlobalUrl = ereol::get_optional<std::string>(j, "eReolenGlobalUrl");

        x.contributors = ereol::get_optional<std::vector<ereol::Contributor>>(j, "contributors");

        x.creators = ereol::get_optional<std::vector<std::string>>(j, "creators");
        x.series = ereol::get_optional<std::vector<std::string>>(j, "series");
        x.subjects = ereol::get_optional<std::vector<std::string>>(j, "subjects");
        x.types = ereol::get_optional<std::vector<std::string>>(j, "types");

    }

    void to_json(json & j, const ereol::Product & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;
        j["title"] = x.title;
        j["publisher"] = x.publisher;
        j["createdDate"] = x.createdDate;
        j["updatedDate"] = x.updatedDate;
        j["cover"] = x.cover;
        j["thumbnail"] = x.thumbnail;
        j["contributors"] = x.contributors;
        j["description"] = x.description;
        j["phid"] = x.phid;
        j["firstPublished"] = x.firstPublished;
        j["language"] = x.language;
        j["duration"] = x.duration;
        j["format"] = x.format;
        j["mediaType"] = x.mediaType;
        j["creators"] = x.creators;
        j["abstract"] = x.abstract;
        j["series"] = x.series;
        j["year"] = x.year;
        j["edition"] = x.edition;
        j["subjects"] = x.subjects;
        j["types"] = x.types;
        j["shelfmark"] = x.shelfmark;
        j["icon"] = x.icon;
        j["seriesPart"] = x.seriesPart;
        j["subscription"] = x.subscription;
        j["eReolenGlobalUrl"] = x.eReolenGlobalUrl;
    }



}

    extern "C" { 
        namespace ereol {
#endif
            Product*  ereol_Product_instantiate()
            {
                return new Product();
            }
            void ereol_Product_delete(Product* m)      
            { 
                delete m; 
            } 
            LoanIdentifier*  ereol_Product_getLoanIdentifier(Product* m) 
            { return &m->loanIdentifier; }
            void   ereol_Product_setLoanIdentifier(Product* m,  LoanIdentifier* identifier) 
            { m->loanIdentifier = *identifier; } 

            const char*  ereol_Product_getTitle(Product* m) 
            { return m->title.c_str(); } 
            void   ereol_Product_setTitle(Product* m,  const char* cp) 
            { m->title.assign(cp); }    
            
            const char*  ereol_Product_getPublisher(Product* m) 
            { return m->publisher.c_str(); } 
            void   ereol_Product_setPublisher(Product* m,  const char* cp) 
            { m->publisher.assign(cp); }    
            
            const char*  ereol_Product_getDescription(Product* m) 
            { return m->description.c_str(); } 
            void   ereol_Product_setDescription(Product* m,  const char* cp) 
            { m->description.assign(cp); }    
            
            const char*  ereol_Product_getLanguage(Product* m) 
            { return m->language.c_str(); } 
            void   ereol_Product_setLanguage(Product* m,  const char* cp) 
            { m->language.assign(cp); }    
            
            const char*  ereol_Product_getMediaType(Product* m) 
            { return m->mediaType.c_str(); } 
            void   ereol_Product_setMediaType(Product* m,  const char* cp) 
            { m->mediaType.assign(cp); }    



            uint64_t  ereol_Product_getCreatedDate(Product* m) 
            { if(!m->createdDate.has_value()){ return 0; } return m->createdDate.value(); } 
            void   ereol_Product_setCreatedDate(Product* m,  uint64_t unix)
            { m->createdDate = std::optional<uint64_t>(unix); }             
            
            uint64_t  ereol_Product_getUpdatedDate(Product* m) 
            { if(!m->updatedDate.has_value()){ return 0; } return m->updatedDate.value(); } 
            void   ereol_Product_setUpdatedDate(Product* m,  uint64_t unix)
            { m->updatedDate = std::optional<uint64_t>(unix); }             
            
            uint64_t  ereol_Product_getFirstPublished(Product* m) 
            { if(!m->firstPublished.has_value()){ return 0; } return m->firstPublished.value(); } 
            void   ereol_Product_setFirstPublished(Product* m,  uint64_t unix)
            { m->firstPublished = std::optional<uint64_t>(unix); }             
            
            uint64_t  ereol_Product_getDuration(Product* m) 
            { if(!m->duration.has_value()){ return 0; } return m->duration.value(); } 
            void   ereol_Product_setDuration(Product* m,  uint64_t unix)
            { m->duration = std::optional<uint64_t>(unix); }             



            const char*  ereol_Product_getProductType(Product* m) 
            { if(!m->productType.has_value()){ return nullptr; } return m->productType.value().c_str(); } 
            void   ereol_Product_setproductType(Product* m,  const char* cp) 
            {if(!m->productType.has_value()){ std::string str(x); m->productType = std::optional<std::string>(str); } else { m->productType.value().assign(cp); } }   
            
            const char*  ereol_Product_getCover(Product* m) 
            { if(!m->cover.has_value()){ return nullptr; } return m->cover.value().c_str(); } 
            void   ereol_Product_setcover(Product* m,  const char* cp) 
            {if(!m->cover.has_value()){ std::string str(x); m->cover = std::optional<std::string>(str); } else { m->cover.value().assign(cp); } }   
            
            const char*  ereol_Product_getPhid(Product* m) 
            { if(!m->phid.has_value()){ return nullptr; } return m->phid.value().c_str(); } 
            void   ereol_Product_setphid(Product* m,  const char* cp) 
            {if(!m->phid.has_value()){ std::string str(x); m->phid = std::optional<std::string>(str); } else { m->phid.value().assign(cp); } }   
            
            const char*  ereol_Product_getThumbnail(Product* m) 
            { if(!m->thumbnail.has_value()){ return nullptr; } return m->thumbnail.value().c_str(); } 
            void   ereol_Product_setthumbnail(Product* m,  const char* cp) 
            {if(!m->thumbnail.has_value()){ std::string str(x); m->thumbnail = std::optional<std::string>(str); } else { m->thumbnail.value().assign(cp); } }   
            
            const char*  ereol_Product_getAbstract(Product* m) 
            { if(!m->abstract.has_value()){ return nullptr; } return m->abstract.value().c_str(); } 
            void   ereol_Product_setabstract(Product* m,  const char* cp) 
            {if(!m->abstract.has_value()){ std::string str(x); m->abstract = std::optional<std::string>(str); } else { m->abstract.value().assign(cp); } }   
            
            const char*  ereol_Product_getYear(Product* m) 
            { if(!m->year.has_value()){ return nullptr; } return m->year.value().c_str(); } 
            void   ereol_Product_setyear(Product* m,  const char* cp) 
            {if(!m->year.has_value()){ std::string str(x); m->year = std::optional<std::string>(str); } else { m->year.value().assign(cp); } }   
            
            const char*  ereol_Product_getEdition(Product* m) 
            { if(!m->edition.has_value()){ return nullptr; } return m->edition.value().c_str(); } 
            void   ereol_Product_setedition(Product* m,  const char* cp) 
            {if(!m->edition.has_value()){ std::string str(x); m->edition = std::optional<std::string>(str); } else { m->edition.value().assign(cp); } }   
            
            const char*  ereol_Product_getShelfmark(Product* m) 
            { if(!m->shelfmark.has_value()){ return nullptr; } return m->shelfmark.value().c_str(); } 
            void   ereol_Product_setshelfmark(Product* m,  const char* cp) 
            {if(!m->shelfmark.has_value()){ std::string str(x); m->shelfmark = std::optional<std::string>(str); } else { m->shelfmark.value().assign(cp); } }   
            
            const char*  ereol_Product_getSeriesPart(Product* m) 
            { if(!m->seriesPart.has_value()){ return nullptr; } return m->seriesPart.value().c_str(); } 
            void   ereol_Product_setseriesPart(Product* m,  const char* cp) 
            {if(!m->seriesPart.has_value()){ std::string str(x); m->seriesPart = std::optional<std::string>(str); } else { m->seriesPart.value().assign(cp); } }   
            
            const char*  ereol_Product_getSubscription(Product* m) 
            { if(!m->subscription.has_value()){ return nullptr; } return m->subscription.value().c_str(); } 
            void   ereol_Product_setsubscription(Product* m,  const char* cp) 
            {if(!m->subscription.has_value()){ std::string str(x); m->subscription = std::optional<std::string>(str); } else { m->subscription.value().assign(cp); } }   
            
            const char*  ereol_Product_getEReolenGlobalUrl(Product* m) 
            { if(!m->eReolenGlobalUrl.has_value()){ return nullptr; } return m->eReolenGlobalUrl.value().c_str(); } 
            void   ereol_Product_seteReolenGlobalUrl(Product* m,  const char* cp) 
            {if(!m->eReolenGlobalUrl.has_value()){ std::string str(x); m->eReolenGlobalUrl = std::optional<std::string>(str); } else { m->eReolenGlobalUrl.value().assign(cp); } }   



            Contributor* ereol_Product_getContributors(Product* m) 
            { if(!m->contributors.has_value()){return nullptr;} return m->contributors.value().data(); } 
            size_t ereol_Product_getContributors_size(Product* m) 
            { if(!m->contributors.has_value()){return 0;} return m->contributors.value().size();} 
            void ereol_Product_getContributors_insert(Product* m, const Contributor* x)
            { if(!m->contributors.has_value()){ m->contributors = std::optional<std::vector<Contributor>>(std::vector<Contributor>()); }  m->contributors.value().push_back(x); } 
            void   ereol_Product_setContributors(Product* m, const  Contributor* arr, size_t n)
            { m->contributors = std::optional<std::vector<Contributor>>(std::vector<Contributor>(arr, arr + n));}   



            VectorStrC* ereol_Product_getCreators(Product* m) 
            { if(!m->creators.has_value()){return nullptr;} return new VectorStrC(&m->creators.value()); } 
            size_t ereol_Product_getCreators_size(Product* m) 
            { if(!m->creators.has_value()){return 0;} return m->creators.value().size();} 
            void ereol_Product_getCreators_insert(Product* m, const char* x) 
            { if(!m->creators.has_value()){ m->creators = std::optional<std::vector<std::string>>(std::vector<std::string>()); } std::string str(x);  m->creators.value().push_back(str); } 
            void   ereol_Product_setCreators(Product* m, const char** arr, size_t n) 
            
            { m->creators = std::optional<std::vector<std::string>>(std::vector<std::string>(arr, arr + n));}   
            VectorStrC* ereol_Product_getSeries(Product* m) 
            { if(!m->series.has_value()){return nullptr;} return new VectorStrC(&m->series.value()); } 
            size_t ereol_Product_getSeries_size(Product* m) 
            { if(!m->series.has_value()){return 0;} return m->series.value().size();} 
            void ereol_Product_getSeries_insert(Product* m, const char* x) 
            { if(!m->series.has_value()){ m->series = std::optional<std::vector<std::string>>(std::vector<std::string>()); } std::string str(x);  m->series.value().push_back(str); } 
            void   ereol_Product_setSeries(Product* m, const char** arr, size_t n) 
            { m->series = std::optional<std::vector<std::string>>(std::vector<std::string>(arr, arr + n));}   
            
            VectorStrC* ereol_Product_getSubjects(Product* m) 
            { if(!m->subjects.has_value()){return nullptr;} return new VectorStrC(&m->subjects.value()); } 
            size_t ereol_Product_getSubjects_size(Product* m) 
            { if(!m->subjects.has_value()){return 0;} return m->subjects.value().size();} 
            void ereol_Product_getSubjects_insert(Product* m, const char* x) 
            { if(!m->subjects.has_value()){ m->subjects = std::optional<std::vector<std::string>>(std::vector<std::string>()); } std::string str(x);  m->subjects.value().push_back(str); } 
            void   ereol_Product_setSubjects(Product* m, const char** arr, size_t n) 
            { m->subjects = std::optional<std::vector<std::string>>(std::vector<std::string>(arr, arr + n));}   

            VectorStrC* ereol_Product_getTypes(Product* m) 
            { if(!m->types.has_value()){return nullptr;} return new VectorStrC(&m->types.value()); } 
            size_t ereol_Product_getTypes_size(Product* m) 
            { if(!m->types.has_value()){return 0;} return m->types.value().size();} 
            void ereol_Product_getTypes_insert(Product* m, const char* x) 
            { if(!m->types.has_value()){ m->types = std::optional<std::vector<std::string>>(std::vector<std::string>()); } std::string str(x);  m->types.value().push_back(str); } 
            void   ereol_Product_setTypes(Product* m, const char** arr, size_t n) 
            { m->types = std::optional<std::vector<std::string>>(std::vector<std::string>(arr, arr + n));}   









#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 