#include <gtest/gtest.h>
#include <math.h> 

double sqrtP (const double) {
	return sqrt(double);
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST (SquareRootTest, PositiveNos) { 
    EXPECT_EQ (18.0, sqrtP (324.0));
    EXPECT_EQ (25.4, sqrtP (645.16));
    EXPECT_EQ (50.3321, sqrtP (2533.310224));
}

TEST (SquareRootTest, ZeroAndNegativeNos) { 
    ASSERT_EQ (0.0, sqrtP (0.0));
    ASSERT_EQ (-1, sqrtP (-22.0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
