#include <algorithm>

#include "gtest/gtest.h"

#include "rectangle.hxx"

using namespace packing;

TEST(Rectangle, EasySort)
{
  std::vector<Rectangle> input = {
    Rectangle(8, 8),
    Rectangle(4, 3),
    Rectangle(4, 3),
    Rectangle(5, 1)
  };

  std::sort(input.begin(), input.end(), Rectangle::BiggerWidth());

  std::vector<Rectangle> sorted = {
    Rectangle(8, 8),
    Rectangle(5, 1),
    Rectangle(4, 3),
    Rectangle(4, 3)
  };

  EXPECT_EQ(input, sorted);
}

TEST(Rectangle, EmptySort)
{
  std::vector<Rectangle> input = {};

  std::sort(input.begin(), input.end(), Rectangle::BiggerWidth());

  EXPECT_TRUE(input.empty());
}
