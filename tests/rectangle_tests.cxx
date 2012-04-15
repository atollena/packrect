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

TEST(Rectangle, BiggerWidth)
{
  auto rec1 = Rectangle(8, 8);
  auto rec2 = Rectangle(4, 3);
  auto rec3 = Rectangle(4, 2);

  EXPECT_TRUE(Rectangle::BiggerWidth()(rec1, rec2));
  EXPECT_FALSE(Rectangle::BiggerWidth()(rec3, rec2));
  EXPECT_FALSE(Rectangle::BiggerWidth()(rec2, rec1));
}
