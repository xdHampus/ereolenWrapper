#include "unity.h"
#include "unity_fixture.h"
#include "src/main/util/InterfaceUtilC.h"
#include "src/main/structs/ChecklistItem.h"
#include "src/main/structs/LibraryProfile.h"
#include "src/main/structs/LoanActive.h"
#include "src/main/structs/LoanHistorical.h"
#include "src/main/structs/LoanIdentifier.h"
#include "src/main/structs/Reservation.h"
#include "src/main/structs/RpcPayload.h"
#include "src/main/structs/Token.h"


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
