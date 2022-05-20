#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(StructTests)
{
  RUN_TEST_CASE(StructTests, ChecklistItemManipulation);
  RUN_TEST_CASE(StructTests, ContributorManipulation);
  RUN_TEST_CASE(StructTests, LibraryProfileManipulation);
  RUN_TEST_CASE(StructTests, LoanActiveManipulation);
  RUN_TEST_CASE(StructTests, LoanHistoricalManipulation);
  RUN_TEST_CASE(StructTests, LoanIdentifierManipulation);
  RUN_TEST_CASE(StructTests, ProductManipulation);
  RUN_TEST_CASE(StructTests, ReservationManipulation);
  RUN_TEST_CASE(StructTests, RpcPayloadManipulation);
  RUN_TEST_CASE(StructTests, TokenManipulation);
}