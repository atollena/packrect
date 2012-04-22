#include "gtest/gtest.h"

#include "rectangle.hxx"
#include "rectangle_position.hxx"

using namespace packing;

TEST(RectanglePosition, Bounds)
{
  auto rec1 = Rectangle(4, 3, 0);
  EXPECT_EQ((size_t) 10, RectanglePosition(Point(0, 0), false).getSides(rec1).size());

  auto rec2 = Rectangle(8, 1, 0);
  EXPECT_EQ((size_t) 16, RectanglePosition(Point(0, 0), false).getSides(rec2).size());
}
