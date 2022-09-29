#include "libfts/summ.hpp"
#include "gtest/gtest.h"

TEST(summTest, zeroAndZero) { EXPECT_EQ(summ(0, 0), 0); }

TEST(summTest, summAnotherPositive) {
  EXPECT_EQ(summ(1, 2), 3);
  EXPECT_EQ(summ(40, 2), 42);
}

TEST(summTest, summAnotherNegative) {
  EXPECT_EQ(summ(-3, 2), -1);
  EXPECT_EQ(summ(10, -5), 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
