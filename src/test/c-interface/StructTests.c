#include "unity.h"
#include "unity_fixture.h"
#include "src/main/util/InterfaceUtilC.h"
#include "src/main/model/ChecklistItem.h"
#include "src/main/model/LibraryProfile.h"
#include "src/main/model/LoanActive.h"
#include "src/main/model/LoanHistorical.h"
#include "src/main/model/LoanIdentifier.h"
#include "src/main/model/Reservation.h"
#include "src/main/model/RpcPayload.h"
#include "src/main/model/Token.h"
#include "src/main/model/Contributor.h"
#include "src/main/model/Record.h"


TEST_GROUP(StructTests);


char* StructTests_LoanIdentifier_identifier = "id sample";
char* StructTests_LoanIdentifier_isbn = "isbn sample";
unsigned long unixSample = 2233561969;

LoanIdentifier* StructTests_CreateLoanIdentifier(){
    LoanIdentifier* loan = ereol_LoanIdentifier_instantiate();
    ereol_LoanIdentifier_setIdentifier(loan, StructTests_LoanIdentifier_identifier);
    ereol_LoanIdentifier_setISBN(loan, StructTests_LoanIdentifier_isbn);
    return loan;
}
void StructTests_VerifyLoanIdentifier(LoanIdentifier* loan, char* id, char* isbn){
    TEST_ASSERT_EQUAL_STRING(id, ereol_LoanIdentifier_getIdentifier(loan));
    TEST_ASSERT_EQUAL_STRING(isbn, ereol_LoanIdentifier_getISBN(loan));
}
char** StructTests_CreateFilled_Array(int n){
    char **strings = (char**)malloc(n*sizeof(char*));
    int i;
    for(i = 0; i < n; i++){
        strings[i] = (char*)malloc(50*sizeof(char));
        sprintf(strings[i], "abc %d", i+1);
    }
    return strings;
}

void StructTests_Compare_Array(char** expected, char** actual, int n){
    int i;
    for(i = 0; i < n; i++){
        TEST_ASSERT_EQUAL_STRING(expected[i], actual[i]);
    }
}
void StructTests_Free_Array(char** arr, int n){
    int i;
    for (i = 0; i < n; ++i)
    {
        free(arr[i]);
    }
    free(arr);
}



TEST_SETUP(StructTests)
{
}

TEST_TEAR_DOWN(StructTests)
{
}

TEST(StructTests, ChecklistItemManipulation)
{
    //Init
    int utcSample = unixSample + 4217;
    ChecklistItem* t = ereol_ChecklistItem_instantiate();
    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    
    StructTests_VerifyLoanIdentifier(loan, StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    
    //Manipulate
    ereol_ChecklistItem_setLoanIdentifier(t, loan);
    ereol_LoanIdentifier_delete(loan);
    ereol_ChecklistItem_setCreationDateUTC(t, utcSample);
    
    //Verify
    StructTests_VerifyLoanIdentifier(ereol_ChecklistItem_getLoanIdentifier(t), StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_EQUAL_INT(utcSample, ereol_ChecklistItem_getCreationDateUTC(t));
    
    ereol_ChecklistItem_delete(t);
}


TEST(StructTests, ContributorManipulation)
{
    //Init
    const char* type = "type str";
    const char* composedName = "composedName str";
    const char* firstName = "firstName str";
    const char* lastName = "lastName str";
    Contributor* t = ereol_Contributor_instantiate();

    //Manipulate
    ereol_Contributor_setType(t, type);
    ereol_Contributor_setComposedName(t, composedName);
    ereol_Contributor_setFirstName(t, firstName);
    ereol_Contributor_setLastName(t, lastName);

    //Verify
    TEST_ASSERT_EQUAL_STRING(type, ereol_Contributor_getType(t));
    TEST_ASSERT_EQUAL_STRING(composedName, ereol_Contributor_getComposedName(t));
    TEST_ASSERT_EQUAL_STRING(firstName, ereol_Contributor_getFirstName(t));
    TEST_ASSERT_EQUAL_STRING(lastName, ereol_Contributor_getLastName(t));

    ereol_Contributor_delete(t);
}



TEST(StructTests, LibraryProfileManipulation)
{
    //Init & Manipulate
    struct LibraryProfile p1 = {1, 2, 3 ,4};
    
    //Verify
    TEST_ASSERT_EQUAL_INT(1, p1.maxConcurrentLoansPerBorrower);
    TEST_ASSERT_EQUAL_INT(2, p1.maxConcurrentReservationsPerBorrower);
    TEST_ASSERT_EQUAL_INT(3, p1.maxConcurrentAudioLoansPerBorrower);
    TEST_ASSERT_EQUAL_INT(4, p1.maxConcurrentAudioReservationsPerBorrower);
}


TEST(StructTests, LoanActiveManipulation)
{
    //Init
    int order = unixSample + 3123;
    int expire = unixSample + 2372;
    char* url = "download url";
    char* retail = "retail number";
    char* internal = "internal number";
    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    bool sub = true;
    LoanActive* t = ereol_LoanActive_instantiate();

    StructTests_VerifyLoanIdentifier(loan, StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_FALSE(ereol_LoanActive_getSubscription(t));

    //Manipulate
    ereol_LoanActive_setLoanIdentifier(t, loan);
    ereol_LoanIdentifier_delete(loan);
    ereol_LoanActive_setOrderDate(t, order);
    ereol_LoanActive_setExpireDate(t, expire);
    ereol_LoanActive_setDownloadUrl(t, url);
    ereol_LoanActive_setRetailerOrderNumber(t, retail);
    ereol_LoanActive_setInternalOrderNumber(t, internal);
    ereol_LoanActive_setSubscription(t, sub);

    //Verify
    StructTests_VerifyLoanIdentifier(ereol_LoanActive_getLoanIdentifier(t), StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_EQUAL_INT(order, ereol_LoanActive_getOrderDate(t));
    TEST_ASSERT_EQUAL_INT(expire, ereol_LoanActive_getExpireDate(t));
    TEST_ASSERT_EQUAL_STRING(url, ereol_LoanActive_getDownloadUrl(t));
    TEST_ASSERT_EQUAL_STRING(retail, ereol_LoanActive_getRetailerOrderNumber(t));
    TEST_ASSERT_EQUAL_STRING(internal, ereol_LoanActive_getInternalOrderNumber(t));
    TEST_ASSERT_TRUE(ereol_LoanActive_getSubscription(t));

    ereol_LoanActive_delete(t);
}


TEST(StructTests, LoanHistoricalManipulation)
{

    //Init
    char* loanId = "loan uid";
    int loanDate = unixSample + 8462;
    bool manual = true;
    const char* title = "title string";
    const char* creator = "creator string";
    const char* pubDate = "creator string";
    char **materialTypes1 = StructTests_CreateFilled_Array(3);
    const char* materialTypeAdd = "abc 4";
    char **materialTypes2 = StructTests_CreateFilled_Array(4);
    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    LoanHistorical* t = ereol_LoanHistorical_instantiate();

    StructTests_VerifyLoanIdentifier(loan, StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_FALSE(ereol_LoanHistorical_getManuallyAdded(t));

    //Manipulate
    ereol_LoanHistorical_setLoanIdentifier(t, loan);
    ereol_LoanIdentifier_delete(loan);
    ereol_LoanHistorical_setLoanId(t, loanId);
    ereol_LoanHistorical_setLoanDate(t, loanDate);
    ereol_LoanHistorical_setManuallyAdded(t, manual);
    ereol_LoanHistorical_setTitle(t, title);
    ereol_LoanHistorical_setCreator(t, creator);
    ereol_LoanHistorical_setPublicationDate(t, pubDate);
    ereol_LoanHistorical_setMaterialTypes(t, materialTypes1, 3);

    //Verify
    StructTests_VerifyLoanIdentifier(ereol_LoanHistorical_getLoanIdentifier(t), StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_EQUAL_STRING(loanId, ereol_LoanHistorical_getLoanId(t));
    TEST_ASSERT_EQUAL_INT(loanDate, ereol_LoanHistorical_getLoanDate(t));
    TEST_ASSERT_TRUE(ereol_LoanHistorical_getManuallyAdded(t));
    TEST_ASSERT_EQUAL_STRING(title, ereol_LoanHistorical_getTitle(t));
    TEST_ASSERT_EQUAL_STRING(creator, ereol_LoanHistorical_getCreator(t));
    TEST_ASSERT_EQUAL_STRING(pubDate, ereol_LoanHistorical_getPublicationDate(t));
    
    //Verify & Manipulate string vector 1
    TEST_ASSERT_EQUAL_INT(3, ereol_LoanHistorical_getMaterialTypes_size(t));
    VectorStrC* m1 = ereol_LoanHistorical_getMaterialTypes(t);
    const char** m1c = ereol_VectorStrC_getData(m1);
    StructTests_Compare_Array(materialTypes1, m1c, 3);
    ereol_VectorStrC_delete(m1);
    StructTests_Free_Array(materialTypes1, 3);
    ereol_LoanHistorical_getMaterialTypes_insert(t, materialTypeAdd);
    //Verify & Manipulate string vector 2
    TEST_ASSERT_EQUAL_INT(4, ereol_LoanHistorical_getMaterialTypes_size(t));
    VectorStrC* m2 = ereol_LoanHistorical_getMaterialTypes(t);
    const char** m2c = ereol_VectorStrC_getData(m2);
    StructTests_Compare_Array(materialTypes2, m2c, 4);
    ereol_VectorStrC_delete(m2);
    StructTests_Free_Array(materialTypes2, 4);
 
    ereol_LoanHistorical_delete(t);
}


TEST(StructTests, LoanIdentifierManipulation)
{
    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    StructTests_VerifyLoanIdentifier(loan, StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    ereol_LoanIdentifier_delete(loan);
}


Contributor* StructTests_FillContributor(const char* t, const char* cn, const char* fn, const char* ln ){
    Contributor* c = ereol_Contributor_instantiate();
    ereol_Contributor_setType(c,t);
    ereol_Contributor_setComposedName(c,cn);
    ereol_Contributor_setFirstName(c,fn);
    ereol_Contributor_setLastName(c,ln);
    return c;
}

void StructTests_CompareContributor(Contributor* a, Contributor* b){
    TEST_ASSERT_EQUAL_STRING(ereol_Contributor_getType(a), ereol_Contributor_getType(b));
    TEST_ASSERT_EQUAL_STRING(ereol_Contributor_getComposedName(a), ereol_Contributor_getComposedName(b));
    TEST_ASSERT_EQUAL_STRING(ereol_Contributor_getFirstName(a), ereol_Contributor_getFirstName(b));
    TEST_ASSERT_EQUAL_STRING(ereol_Contributor_getLastName(a), ereol_Contributor_getLastName(b));
}

TEST(StructTests, RecordManipulation)
{

    //Init
    const char* title = "title string";
    const char* publisher = "publisher string";
    const char* description = "description string";
    const char* language = "language string";
    const char* mediaType = "mediaType string";

    int createdDate = unixSample + 84642;
    int updatedDate = unixSample + 2462;
    int firstPublished = unixSample + 14962;
    int duration = unixSample + 45462;

    const char* recordType = "recordType string";
    const char* cover = "cover string";
    const char* phid = "phid string";
    const char* format = "format string";
    const char* thumbnail = "thumbnail string";
    const char* abstract = "abstract string";
    const char* year = "year string";
    const char* edition = "edition string";
    const char* shelfmark = "shelfmark string";
    const char* seriesPart = "seriesPart string";
    const char* subscription = "subscription string";
    const char* eReolenGlobalUrl = "eReolenGlobalUrl string";

    Contributor* cAdd1 = StructTests_FillContributor("t1","cn1","fn1","ln1"); 
    Contributor* cAdd2 = StructTests_FillContributor("t2","cn2","fn2","ln2"); 
    Contributor* cAdd3 = StructTests_FillContributor("t3","cn3","fn3","ln3");
    Contributor* c1a[2];
    c1a[0] = cAdd1;
    c1a[1] = cAdd2;
    Contributor* c2a[3];
    c2a[0] = cAdd1;
    c2a[1] = cAdd2;
    c2a[2] = cAdd3;
    Contributor** c1 = c1a;
    Contributor** c2 = c2a;


    char **m1 = StructTests_CreateFilled_Array(3);
    const char* mAdd = "abc 4";
    char **m2 = StructTests_CreateFilled_Array(4);

    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    Record* t = ereol_Record_instantiate();
    StructTests_VerifyLoanIdentifier(loan, StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);

    //Manipulate
    ereol_Record_setLoanIdentifier(t, loan);
    ereol_LoanIdentifier_delete(loan);
    ereol_Record_setTitle(t, title);
    ereol_Record_setPublisher(t, publisher);
    ereol_Record_setDescription(t, description);
    ereol_Record_setLanguage(t, language);
    ereol_Record_setMediaType(t, mediaType);
    ereol_Record_setCreatedDate(t, createdDate);
    ereol_Record_setUpdatedDate(t, updatedDate);
    ereol_Record_setFirstPublished(t, firstPublished);
    ereol_Record_setDuration(t, duration);
    ereol_Record_setRecordType(t, recordType);
    ereol_Record_setCover(t, cover);
    ereol_Record_setPhid(t, phid);
    ereol_Record_setFormat(t, format);
    ereol_Record_setThumbnail(t, thumbnail);
    ereol_Record_setAbstract(t, abstract);
    ereol_Record_setYear(t, year);
    ereol_Record_setEdition(t, edition);
    ereol_Record_setShelfmark(t, shelfmark);
    ereol_Record_setSeriesPart(t, seriesPart);
    ereol_Record_setSubscription(t, subscription);
    ereol_Record_setEReolenGlobalUrl(t, eReolenGlobalUrl);
    ereol_Record_setContributors(t, c1, 2);
    ereol_Record_setCreators(t, m1, 3);
    ereol_Record_setSeries(t, m1, 3);
    ereol_Record_setSubjects(t, m1, 3);
    ereol_Record_setTypes(t, m1, 3);


    //Verify
    StructTests_VerifyLoanIdentifier(ereol_LoanHistorical_getLoanIdentifier(t), StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_EQUAL_STRING(title, ereol_Record_getTitle(t));
    TEST_ASSERT_EQUAL_STRING(publisher, ereol_Record_getPublisher(t));
    TEST_ASSERT_EQUAL_STRING(description, ereol_Record_getDescription(t));
    TEST_ASSERT_EQUAL_STRING(language, ereol_Record_getLanguage(t));
    TEST_ASSERT_EQUAL_STRING(mediaType, ereol_Record_getMediaType(t));
    TEST_ASSERT_EQUAL_INT(createdDate, ereol_Record_getCreatedDate(t));
    TEST_ASSERT_EQUAL_INT(updatedDate, ereol_Record_getUpdatedDate(t));
    TEST_ASSERT_EQUAL_INT(firstPublished, ereol_Record_getFirstPublished(t));
    TEST_ASSERT_EQUAL_INT(duration, ereol_Record_getDuration(t));
    TEST_ASSERT_EQUAL_STRING(recordType, ereol_Record_getRecordType(t));
    TEST_ASSERT_EQUAL_STRING(cover, ereol_Record_getCover(t));
    TEST_ASSERT_EQUAL_STRING(phid, ereol_Record_getPhid(t));
    TEST_ASSERT_EQUAL_STRING(format, ereol_Record_getFormat(t));
    TEST_ASSERT_EQUAL_STRING(thumbnail, ereol_Record_getThumbnail(t));
    TEST_ASSERT_EQUAL_STRING(abstract, ereol_Record_getAbstract(t));
    TEST_ASSERT_EQUAL_STRING(year, ereol_Record_getYear(t));
    TEST_ASSERT_EQUAL_STRING(edition, ereol_Record_getEdition(t));
    TEST_ASSERT_EQUAL_STRING(shelfmark, ereol_Record_getShelfmark(t));
    TEST_ASSERT_EQUAL_STRING(seriesPart, ereol_Record_getSeriesPart(t));
    TEST_ASSERT_EQUAL_STRING(subscription, ereol_Record_getSubscription(t));
    TEST_ASSERT_EQUAL_STRING(eReolenGlobalUrl, ereol_Record_getEReolenGlobalUrl(t));

    TEST_ASSERT_EQUAL_INT(2, ereol_Record_getContributors_size(t));
    VectorVoid* vectVoid1 = ereol_Record_getContributors(t);
    Contributor** cr1 = (Contributor**)ereol_VectorVoid_getData(vectVoid1);
    for(int i = 0; i < 2; i++){
        StructTests_CompareContributor(c1[i], cr1[i]);
    }
    ereol_VectorVoid_delete(vectVoid1);
    ereol_Record_getContributors_insert(t, cAdd3);
    TEST_ASSERT_EQUAL_INT(3, ereol_Record_getContributors_size(t));
    VectorVoid* vectVoid2 = ereol_Record_getContributors(t);
    Contributor** cr2 = (Contributor**)ereol_VectorVoid_getData(vectVoid2);
    for(int i = 0; i < 3; i++){
        StructTests_CompareContributor(c2[i], cr2[i]);
    }
    ereol_VectorVoid_delete(vectVoid2);
    ereol_Contributor_delete(cAdd1);
    ereol_Contributor_delete(cAdd2);
    ereol_Contributor_delete(cAdd3);


    TEST_ASSERT_EQUAL_INT(3, ereol_Record_getCreators_size(t));
    TEST_ASSERT_EQUAL_INT(3, ereol_Record_getSeries_size(t));
    TEST_ASSERT_EQUAL_INT(3, ereol_Record_getSubjects_size(t));
    TEST_ASSERT_EQUAL_INT(3, ereol_Record_getTypes_size(t));
    
    //Verify & Manipulate string vector 1
    VectorStrC* m1r = ereol_Record_getCreators(t);
    StructTests_Compare_Array(m1, ereol_VectorStrC_getData(m1r), 3);
    ereol_VectorStrC_delete(m1r);
    m1r = ereol_Record_getSeries(t);
    StructTests_Compare_Array(m1, ereol_VectorStrC_getData(m1r), 3);
    ereol_VectorStrC_delete(m1r);
    m1r = ereol_Record_getSubjects(t);
    StructTests_Compare_Array(m1, ereol_VectorStrC_getData(m1r), 3);
    ereol_VectorStrC_delete(m1r);
    m1r = ereol_Record_getTypes(t);
    StructTests_Compare_Array(m1, ereol_VectorStrC_getData(m1r), 3);
    ereol_VectorStrC_delete(m1r);

    //Verify & Manipulate string vector 2
    ereol_Record_getCreators_insert(t, mAdd);
    ereol_Record_getSeries_insert(t, mAdd);
    ereol_Record_getSubjects_insert(t, mAdd);
    ereol_Record_getTypes_insert(t, mAdd);
    TEST_ASSERT_EQUAL_INT(4, ereol_Record_getCreators_size(t));
    TEST_ASSERT_EQUAL_INT(4, ereol_Record_getSeries_size(t));
    TEST_ASSERT_EQUAL_INT(4, ereol_Record_getSubjects_size(t));
    TEST_ASSERT_EQUAL_INT(4, ereol_Record_getTypes_size(t));
    VectorStrC* m2r = ereol_Record_getCreators(t);
    StructTests_Compare_Array(m2, ereol_VectorStrC_getData(m2r), 4);
    ereol_VectorStrC_delete(m2r);
    m2r = ereol_Record_getSeries(t);
    StructTests_Compare_Array(m2, ereol_VectorStrC_getData(m2r), 4);
    ereol_VectorStrC_delete(m2r);
    m2r = ereol_Record_getSubjects(t);
    StructTests_Compare_Array(m2, ereol_VectorStrC_getData(m2r), 4);
    ereol_VectorStrC_delete(m2r);
    m2r = ereol_Record_getTypes(t);
    StructTests_Compare_Array(m2, ereol_VectorStrC_getData(m2r), 4);
    ereol_VectorStrC_delete(m2r);
    StructTests_Free_Array(m1, 3);
    StructTests_Free_Array(m2, 4);

    ereol_Record_delete(t);
}




TEST(StructTests, ReservationManipulation)
{
    //Init
    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    char* bookId   = "book id str";
    char* status   = "status str";
    int created    = unixSample  + 21313;
    int expire     = unixSample  + 8123;
    int redeem     = unixSample  + 31412;
    Reservation* t = ereol_Reservation_instantiate();

    //Manipulate
    ereol_Reservation_setLoanIdentifier(t, loan);
    ereol_LoanIdentifier_delete(loan);
    ereol_Reservation_setBookId(t, bookId);
    ereol_Reservation_setStatus(t, status);
    ereol_Reservation_setCreatedUTC(t, created);
    ereol_Reservation_setExpireUTC(t, expire);
    ereol_Reservation_setExpectedRedeemDateUTC(t, redeem);

    //Verify
    StructTests_VerifyLoanIdentifier(ereol_Reservation_getLoanIdentifier(t), StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_EQUAL_STRING(bookId, ereol_Reservation_getBookId(t));
    TEST_ASSERT_EQUAL_STRING(status, ereol_Reservation_getStatus(t));
    TEST_ASSERT_EQUAL_INT(created, ereol_Reservation_getCreatedUTC(t));
    TEST_ASSERT_EQUAL_INT(expire, ereol_Reservation_getExpireUTC(t));
    TEST_ASSERT_EQUAL_INT(redeem, ereol_Reservation_getExpectedRedeemDateUTC(t));

    ereol_Reservation_delete(t);
}





TEST(StructTests, RpcPayloadManipulation)
{

    //Init
    const char* jsonrpc = "jsonrpc string";
    const char* method = "method string";
    const char* id = "id string";
    char ** params1 = StructTests_CreateFilled_Array(3);
    const char* paramToAdd = "abc 4";
    char ** params2 = StructTests_CreateFilled_Array(4);

    RpcPayload* t = ereol_RpcPayload_instantiate();

    //Manipulate
    ereol_RpcPayload_setJsonRPC(t, jsonrpc);
    ereol_RpcPayload_setMethod(t, method);
    ereol_RpcPayload_setId(t, id);
    ereol_RpcPayload_setParams(t, params1, 3);

    //Verify
    TEST_ASSERT_EQUAL_STRING(jsonrpc, ereol_RpcPayload_getJsonRPC(t));
    TEST_ASSERT_EQUAL_STRING(method, ereol_RpcPayload_getMethod(t));
    TEST_ASSERT_EQUAL_STRING(id, ereol_RpcPayload_getId(t));
    
    //Verify & Manipulate string vector 1
    TEST_ASSERT_EQUAL_INT(3, ereol_RpcPayload_getParams_size(t));
    VectorStrC* m1 = ereol_RpcPayload_getParams(t);
    const char** m1c = ereol_VectorStrC_getData(m1);
    StructTests_Compare_Array(params1, m1c, 3);
    ereol_VectorStrC_delete(m1);
    StructTests_Free_Array(params1, 3);
    ereol_RpcPayload_getParams_insert(t, paramToAdd);
    //Verify & Manipulate string vector 2
    TEST_ASSERT_EQUAL_INT(4, ereol_RpcPayload_getParams_size(t));
    VectorStrC* m2 = ereol_RpcPayload_getParams(t);
    const char** m2c = ereol_VectorStrC_getData(m2);
    StructTests_Compare_Array(params2, m2c, 4);
    ereol_VectorStrC_delete(m2);
    StructTests_Free_Array(params2, 4);
 
    ereol_RpcPayload_delete(t);
}

TEST(StructTests, TokenManipulation)
{
    //Init
    int timeFetched = unixSample + 13763;
    const char* sessid = "sessid str";
    const char* expirationDate = "expirationDate str";
    Token* t = ereol_Token_instantiate();
    enum Library lib = ROSKILDE;

    //Manipulate
    ereol_Token_setTimeFetched(t, timeFetched);
    ereol_Token_setSessid(t, sessid);
    ereol_Token_setExpirationDate(t, expirationDate);
    ereol_Token_setLibrary(t, lib);

    //Verify
    TEST_ASSERT_EQUAL_INT(timeFetched, ereol_Token_getTimeFetched(t));
    TEST_ASSERT_EQUAL_STRING(sessid, ereol_Token_getSessid(t));
    TEST_ASSERT_EQUAL_STRING(expirationDate, ereol_Token_getExpirationDate(t));
    TEST_ASSERT_TRUE(lib == ereol_Token_getLibrary(t));

    ereol_Token_delete(t);
}
