#include "gtest/gtest.h"
#include "rectangle.hxx"
#include "optimal_rectangle_packing.hxx"

#include <iostream>

using namespace packing;

TEST(OPTIMAL_RECTANGLE_PACKING, EXAMPLE)
{
  const std::vector<Rectangle> input = {
    Rectangle(8, 8),
    Rectangle(4, 3),
    Rectangle(3, 4)
  };

  std::cout << OptimalRectanglePacking(input).compute();
    
  EXPECT_EQ(88, OptimalRectanglePacking(input).compute());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

