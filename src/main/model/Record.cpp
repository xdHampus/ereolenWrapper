#include "Record.h"
#include "../util/InterfaceUtilC.h"
#ifdef __cplusplus 
#include <functional>
#include <vector>

#include <cstring>
#include <cstdlib>
#include "../util/JSONHelper.h"

void ereol::from_json(const std::string  &s, ereol::Record& x){
    nlohmann::json j = nlohmann::json::parse(s);
    x = j;
}
void ereol::to_json(std::string & s, const ereol::Record & x){
    nlohmann::json j = x;
    s = j.dump();
}

namespace nlohmann {

    void from_json(const json & j, ereol::Record& x) {
        x.loanIdentifier.identifier = j.at("identifier").get<std::string>();
        x.loanIdentifier.isbn = j.at("isbn").get<std::string>();        
        x.title = j.at("title").get<std::string>();
        x.publisher = j.at("publisher").get<std::string>();
        x.description = j.at("description").get<std::string>();
        x.language = j.at("language").get<std::string>();
        x.mediaType = j.at("mediaType").get<std::string>();

        x.createdDate = ereol::get_optional<int64_t>(j, "createdDate");
        x.updatedDate = ereol::get_optional<int64_t>(j, "updatedDate");
        x.firstPublished = ereol::get_optional<int64_t>(j, "firstPublished");
        x.duration = ereol::get_optional<int64_t>(j, "duration");

        x.recordType = ereol::get_optional<std::string>(j, "icon");
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

    void to_json(json & j, const ereol::Record & x) {
        j = json::object();
        j["identifier"] = x.loanIdentifier.identifier;
        j["isbn"] = x.loanIdentifier.isbn;
        j["title"] = x.title;
        j["publisher"] = x.publisher;
        j["description"] = x.description;
        j["language"] = x.language;
        j["mediaType"] = x.mediaType;

        j["createdDate"] = x.createdDate.value();
        j["updatedDate"] = x.updatedDate.value();
        j["firstPublished"] = x.firstPublished.value();
        j["duration"] = x.duration.value();

        j["icon"] = x.recordType.value();
        j["cover"] = x.cover.value();
        j["phid"] = x.phid.value();
        j["format"] = x.format.value();
        j["thumbnail"] = x.thumbnail.value();
        j["abstract"] = x.abstract.value();
        j["year"] = x.year.value();
        j["edition"] = x.edition.value();
        j["shelfmark"] = x.shelfmark.value();
        j["seriesPart"] = x.seriesPart.value();
        j["subscription"] = x.subscription.value();
        j["eReolenGlobalUrl"] = x.eReolenGlobalUrl.value();

        j["contributors"] = x.contributors.value();

        j["creators"] = x.creators.value();
        j["series"] = x.series.value();
        j["subjects"] = x.subjects.value();
        j["types"] = x.types.value();

    }



}

    extern "C" { 
        namespace ereol {
#endif

            Record*  ereol_Record_instantiate()
            {
                return new Record();
            }
            void ereol_Record_delete(Record* m)      
            { 
                delete m; 
            } 
            LoanIdentifier*  ereol_Record_getLoanIdentifier(Record* m) 
            { return &m->loanIdentifier; }
            void   ereol_Record_setLoanIdentifier(Record* m,  LoanIdentifier* identifier) 
            { m->loanIdentifier = *identifier; } 

            const char*  ereol_Record_getTitle(Record* m) 
            { return m->title.c_str(); } 
            void   ereol_Record_setTitle(Record* m,  const char* cp) 
            { m->title.assign(cp); }    
            
            const char*  ereol_Record_getPublisher(Record* m) 
            { return m->publisher.c_str(); } 
            void   ereol_Record_setPublisher(Record* m,  const char* cp) 
            { m->publisher.assign(cp); }    
            
            const char*  ereol_Record_getDescription(Record* m) 
            { return m->description.c_str(); } 
            void   ereol_Record_setDescription(Record* m,  const char* cp) 
            { m->description.assign(cp); }    
            
            const char*  ereol_Record_getLanguage(Record* m) 
            { return m->language.c_str(); } 
            void   ereol_Record_setLanguage(Record* m,  const char* cp) 
            { m->language.assign(cp); }    
            
            const char*  ereol_Record_getMediaType(Record* m) 
            { return m->mediaType.c_str(); } 
            void   ereol_Record_setMediaType(Record* m,  const char* cp) 
            { m->mediaType.assign(cp); }    



            int64_t ereol_Record_getCreatedDate(Record* m) 
            { if(!m->createdDate.has_value()){ return 0; } return m->createdDate.value(); } 
            void   ereol_Record_setCreatedDate(Record* m,  int64_t unixTime)
            { m->createdDate = std::optional<int64_t>(unixTime); }            

            int64_t  ereol_Record_getUpdatedDate(Record* m) 
            { if(!m->updatedDate.has_value()){ return 0; } return m->updatedDate.value(); } 
            void   ereol_Record_setUpdatedDate(Record* m,  int64_t unixTime)
            { m->updatedDate = std::optional<int64_t>(unixTime); }             
            
            int64_t  ereol_Record_getFirstPublished(Record* m) 
            { if(!m->firstPublished.has_value()){ return 0; } return m->firstPublished.value(); } 
            void   ereol_Record_setFirstPublished(Record* m,  int64_t unixTime)
            { m->firstPublished = std::optional<int64_t>(unixTime); }             
            
            int64_t  ereol_Record_getDuration(Record* m) 
            { if(!m->duration.has_value()){ return 0; } return m->duration.value(); } 
            void   ereol_Record_setDuration(Record* m, int64_t unixTime)
            { m->duration = std::optional<int64_t>(unixTime); }             



            const char*  ereol_Record_getRecordType(Record* m) 
            { if(!m->recordType.has_value()){ return nullptr; } return m->recordType.value().c_str(); } 
            void   ereol_Record_setRecordType(Record* m,  const char* cp) 
            {if(!m->recordType.has_value()){ std::string str(cp); m->recordType = std::optional<std::string>(str); } else { m->recordType.value().assign(cp); } }   
            
            const char*  ereol_Record_getCover(Record* m) 
            { if(!m->cover.has_value()){ return nullptr; } return m->cover.value().c_str(); } 
            void   ereol_Record_setCover(Record* m,  const char* cp) 
            {if(!m->cover.has_value()){ std::string str(cp); m->cover = std::optional<std::string>(str); } else { m->cover.value().assign(cp); } }   
            
            const char*  ereol_Record_getPhid(Record* m) 
            { if(!m->phid.has_value()){ return nullptr; } return m->phid.value().c_str(); } 
            void   ereol_Record_setPhid(Record* m,  const char* cp) 
            {if(!m->phid.has_value()){ std::string str(cp); m->phid = std::optional<std::string>(str); } else { m->phid.value().assign(cp); } }   
            
            const char*  ereol_Record_getFormat(Record* m) 
            { if(!m->format.has_value()){ return nullptr; } return m->format.value().c_str(); } 
            void   ereol_Record_setFormat(Record* m,  const char* cp) 
            {if(!m->format.has_value()){ std::string str(cp); m->format = std::optional<std::string>(str); } else { m->format.value().assign(cp); } }   
            

            const char*  ereol_Record_getThumbnail(Record* m) 
            { if(!m->thumbnail.has_value()){ return nullptr; } return m->thumbnail.value().c_str(); } 
            void   ereol_Record_setThumbnail(Record* m,  const char* cp) 
            {if(!m->thumbnail.has_value()){ std::string str(cp); m->thumbnail = std::optional<std::string>(str); } else { m->thumbnail.value().assign(cp); } }   
            
            const char*  ereol_Record_getAbstract(Record* m) 
            { if(!m->abstract.has_value()){ return nullptr; } return m->abstract.value().c_str(); } 
            void   ereol_Record_setAbstract(Record* m,  const char* cp) 
            {if(!m->abstract.has_value()){ std::string str(cp); m->abstract = std::optional<std::string>(str); } else { m->abstract.value().assign(cp); } }   
            
            const char*  ereol_Record_getYear(Record* m) 
            { if(!m->year.has_value()){ return nullptr; } return m->year.value().c_str(); } 
            void   ereol_Record_setYear(Record* m,  const char* cp) 
            {if(!m->year.has_value()){ std::string str(cp); m->year = std::optional<std::string>(str); } else { m->year.value().assign(cp); } }   
            
            const char*  ereol_Record_getEdition(Record* m) 
            { if(!m->edition.has_value()){ return nullptr; } return m->edition.value().c_str(); } 
            void   ereol_Record_setEdition(Record* m,  const char* cp) 
            {if(!m->edition.has_value()){ std::string str(cp); m->edition = std::optional<std::string>(str); } else { m->edition.value().assign(cp); } }   
            
            const char*  ereol_Record_getShelfmark(Record* m) 
            { if(!m->shelfmark.has_value()){ return nullptr; } return m->shelfmark.value().c_str(); } 
            void   ereol_Record_setShelfmark(Record* m,  const char* cp) 
            {if(!m->shelfmark.has_value()){ std::string str(cp); m->shelfmark = std::optional<std::string>(str); } else { m->shelfmark.value().assign(cp); } }   
            
            const char*  ereol_Record_getSeriesPart(Record* m) 
            { if(!m->seriesPart.has_value()){ return nullptr; } return m->seriesPart.value().c_str(); } 
            void   ereol_Record_setSeriesPart(Record* m,  const char* cp) 
            {if(!m->seriesPart.has_value()){ std::string str(cp); m->seriesPart = std::optional<std::string>(str); } else { m->seriesPart.value().assign(cp); } }   
            
            const char*  ereol_Record_getSubscription(Record* m) 
            { if(!m->subscription.has_value()){ return nullptr; } return m->subscription.value().c_str(); } 
            void   ereol_Record_setSubscription(Record* m,  const char* cp) 
            {if(!m->subscription.has_value()){ std::string str(cp); m->subscription = std::optional<std::string>(str); } else { m->subscription.value().assign(cp); } }   
            
            const char*  ereol_Record_getEReolenGlobalUrl(Record* m) 
            { if(!m->eReolenGlobalUrl.has_value()){ return nullptr; } return m->eReolenGlobalUrl.value().c_str(); } 
            void   ereol_Record_setEReolenGlobalUrl(Record* m,  const char* cp) 
            {if(!m->eReolenGlobalUrl.has_value()){ std::string str(cp); m->eReolenGlobalUrl = std::optional<std::string>(str); } else { m->eReolenGlobalUrl.value().assign(cp); } }   


            VectorVoid* ereol_Record_getContributors(Record* m) 
            { 
                if(!m->contributors.has_value()){return nullptr;} 
                return new ereol::VectorVoid(m->contributors.value());
            } 
            size_t ereol_Record_getContributors_size(Record* m) 
            { if(!m->contributors.has_value()){return 0;} return m->contributors.value().size();} 
            void ereol_Record_getContributors_insert(Record* m, const Contributor* x)
            { if(!m->contributors.has_value()){ m->contributors = std::optional<std::vector<Contributor>>(std::vector<Contributor>()); } m->contributors.value().push_back(*x); } 
            void   ereol_Record_setContributors(Record* m, const  Contributor** arr, size_t n)
            { 
                std::vector<Contributor> v;
                v.reserve(n);
                int i;
                for(i = 0; i < n; i++){
                    Contributor cont = *arr[i];
                    v.push_back(cont);
                }
                m->contributors = std::optional<std::vector<Contributor>>(v);
            }   



            VectorStrC* ereol_Record_getCreators(Record* m) 
            { if(!m->creators.has_value()){return nullptr;} return new VectorStrC(&m->creators.value()); } 
            size_t ereol_Record_getCreators_size(Record* m) 
            { if(!m->creators.has_value()){return 0;} return m->creators.value().size();} 
            void ereol_Record_getCreators_insert(Record* m, const char* x) 
            { if(!m->creators.has_value()){ m->creators = std::optional<std::vector<std::string>>(std::vector<std::string>()); } std::string str(x);  m->creators.value().push_back(str); } 
            void   ereol_Record_setCreators(Record* m, const char** arr, size_t n) 
            
            { m->creators = std::optional<std::vector<std::string>>(std::vector<std::string>(arr, arr + n));}   
            VectorStrC* ereol_Record_getSeries(Record* m) 
            { if(!m->series.has_value()){return nullptr;} return new VectorStrC(&m->series.value()); } 
            size_t ereol_Record_getSeries_size(Record* m) 
            { if(!m->series.has_value()){return 0;} return m->series.value().size();} 
            void ereol_Record_getSeries_insert(Record* m, const char* x) 
            { if(!m->series.has_value()){ m->series = std::optional<std::vector<std::string>>(std::vector<std::string>()); } std::string str(x);  m->series.value().push_back(str); } 
            void   ereol_Record_setSeries(Record* m, const char** arr, size_t n) 
            { m->series = std::optional<std::vector<std::string>>(std::vector<std::string>(arr, arr + n));}   
            
            VectorStrC* ereol_Record_getSubjects(Record* m) 
            { if(!m->subjects.has_value()){return nullptr;} return new VectorStrC(&m->subjects.value()); } 
            size_t ereol_Record_getSubjects_size(Record* m) 
            { if(!m->subjects.has_value()){return 0;} return m->subjects.value().size();} 
            void ereol_Record_getSubjects_insert(Record* m, const char* x) 
            { if(!m->subjects.has_value()){ m->subjects = std::optional<std::vector<std::string>>(std::vector<std::string>()); } std::string str(x);  m->subjects.value().push_back(str); } 
            void   ereol_Record_setSubjects(Record* m, const char** arr, size_t n) 
            { m->subjects = std::optional<std::vector<std::string>>(std::vector<std::string>(arr, arr + n));}   

            VectorStrC* ereol_Record_getTypes(Record* m) 
            { if(!m->types.has_value()){return nullptr;} return new VectorStrC(&m->types.value()); } 
            size_t ereol_Record_getTypes_size(Record* m) 
            { if(!m->types.has_value()){return 0;} return m->types.value().size();} 
            void ereol_Record_getTypes_insert(Record* m, const char* x) 
            { if(!m->types.has_value()){ m->types = std::optional<std::vector<std::string>>(std::vector<std::string>()); } std::string str(x);  m->types.value().push_back(str); } 
            void   ereol_Record_setTypes(Record* m, const char** arr, size_t n) 
            { m->types = std::optional<std::vector<std::string>>(std::vector<std::string>(arr, arr + n));}   


#ifdef __cplusplus 
    };
}
#endif  // __cplusplus 