#include "gtest/gtest.h"
#include "rectangle.hxx"
#include "min_area.hxx"

#include <iostream>

using namespace packing;

TEST(MIN_AREA, EXAMPLE)
{
  const std::vector<Rectangle> input = {
    Rectangle(8, 8),
    Rectangle(4, 3),
    Rectangle(3, 4)
  };

  std::cout << MinArea(input).compute();
    
  EXPECT_EQ(88, MinArea(input).compute());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

