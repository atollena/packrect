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

