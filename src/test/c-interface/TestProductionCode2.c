#include "unity.h"
#include "unity_fixture.h"
#include "src/main/structs/LoanIdentifier.h"
#include "src/main/structs/ChecklistItem.h"
#include "src/main/structs/LoanActive.h"

TEST_GROUP(ProductionCode2);

/* These should be ignored because they are commented out in various ways:
#include "whatever.h"
*/
//#include "somethingelse.h"
char* StructTests_LoanIdentifier_identifier = "id sample";
char* StructTests_LoanIdentifier_isbn = "isbn sample";

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

TEST_SETUP(ProductionCode2)
{
}

TEST_TEAR_DOWN(ProductionCode2)
{
}

TEST(ProductionCode2, IgnoredTest)
{
    TEST_IGNORE_MESSAGE("This Test Was Ignored On Purpose");
}

TEST(ProductionCode2, LoanIdentifierManipulation)
{
    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    
    StructTests_VerifyLoanIdentifier(loan, StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    
    ereol_LoanIdentifier_delete(loan);
}
TEST(ProductionCode2, ChecklistItemManipulation)
{
    int utcSample = 1313;
    ChecklistItem* t = ereol_ChecklistItem_instantiate();
    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    
    StructTests_VerifyLoanIdentifier(loan, StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    
    ereol_ChecklistItem_setLoanIdentifier(t, loan);
    ereol_ChecklistItem_setCreationDateUTC(t, utcSample);
    
    StructTests_VerifyLoanIdentifier(ereol_ChecklistItem_getLoanIdentifier(t), StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_EQUAL_INT(utcSample, ereol_ChecklistItem_getCreationDateUTC(t));
    ereol_ChecklistItem_delete(t);
}
TEST(ProductionCode2, LoanActiveManipulation)
{
    int order = 1313;
    int expire = 8123;
    char* url = "download url";
    char* retail = "retail number";
    char* internal = "internal number";
    LoanActive* t = ereol_LoanActive_instantiate();
    LoanIdentifier* loan = StructTests_CreateLoanIdentifier();
    bool sub = true;

    StructTests_VerifyLoanIdentifier(loan, StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_FALSE(ereol_LoanActive_getSubscription(t));

    ereol_LoanActive_setLoanIdentifier(t, loan);
    ereol_LoanActive_setOrderDate(t, order);
    ereol_LoanActive_setExpireDate(t, expire);
    ereol_LoanActive_setDownloadUrl(t, url);
    ereol_LoanActive_setRetailerOrderNumber(t, retail);
    ereol_LoanActive_setInternalOrderNumber(t, internal);
    ereol_LoanActive_setSubscription(t, sub);

    StructTests_VerifyLoanIdentifier(ereol_LoanActive_getLoanIdentifier(t), StructTests_LoanIdentifier_identifier, StructTests_LoanIdentifier_isbn);
    TEST_ASSERT_EQUAL_INT(order, ereol_LoanActive_getOrderDate(t));
    TEST_ASSERT_EQUAL_INT(expire, ereol_LoanActive_getExpireDate(t));
    TEST_ASSERT_EQUAL_STRING(url, ereol_LoanActive_getDownloadUrl(t));
    TEST_ASSERT_EQUAL_STRING(retail, ereol_LoanActive_getRetailerOrderNumber(t));
    TEST_ASSERT_EQUAL_STRING(internal, ereol_LoanActive_getInternalOrderNumber(t));
    TEST_ASSERT_TRUE(ereol_LoanActive_getSubscription(t));

    ereol_LoanActive_delete(t);
}