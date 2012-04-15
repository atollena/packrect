#include "gtest/gtest.h"
#include "rectangle.hxx"
#include "optimal_rectangle_packing.hxx"
#include "rectangle_containment_solver.hxx"

using namespace packing;

TEST(OptimalRectanglePacking, SiteExample)
{
  const std::vector<Rectangle> input = {
    Rectangle(8, 8),
    Rectangle(4, 3),
    Rectangle(4, 3)
  };

  EXPECT_EQ(OptimalRectanglePacking(input).compute().first.area(), 88);
}

TEST(OptimalRectanglePacking, Square10)
{
  std::vector<Rectangle> input;
  for(int i = 1; i <= 10; i++) {
    input.push_back(Rectangle(i, i));
  }

  EXPECT_EQ(OptimalRectanglePacking(input).compute().first.area(), 15*27);
}

TEST(OptimalRectanglePacking, Rectangle10)
{
  std::vector<Rectangle> input;
  for(int i = 0; i < 10; i++) {
    input.push_back(Rectangle(i + 1, i));
  }

  EXPECT_EQ(OptimalRectanglePacking(input).compute().first.area(), 17*26);
}
