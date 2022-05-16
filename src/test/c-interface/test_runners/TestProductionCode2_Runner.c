#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(ProductionCode2)
{
  RUN_TEST_CASE(ProductionCode2, IgnoredTest);
  RUN_TEST_CASE(ProductionCode2, LoanIdentifierManipulation);
  RUN_TEST_CASE(ProductionCode2, ChecklistItemManipulation);
  RUN_TEST_CASE(ProductionCode2, LoanActiveManipulation);
}