#include "unity_fixture.h"

static void runAllTests(void)
{
  RUN_TEST_GROUP(StructTests);
}

int main(int argc, const char* argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
