#include "gtest/gtest.h"

#include "cube.h"

TEST(CubeTest, GetSize) {
  Cube cube(/*size=*/4);
  EXPECT_EQ(4, cube.GetSize());
}
