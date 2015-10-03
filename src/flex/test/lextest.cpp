#include <iostream>
#include "gtest/gtest.h"

TEST(IndependentMethod, OneIsOne) {
  EXPECT_EQ(1, 1);
}

TEST(FailTest, IsOneTwo) {
  EXPECT_NE(1, 2);
}
