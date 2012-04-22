#include "gtest/gtest.h"

#include "tests_helpers.hxx"
#include "rectangle.hxx"
#include "optimal_rectangle_packing.hxx"
#include "rectangle_containment_solver.hxx"
#include "solution_to_string.hxx"

using namespace packing;

TEST(OptimalRectanglePacking, SiteExample)
{
  auto input = {
    Rectangle(8, 8, 1),
    Rectangle(4, 3, 2),
    Rectangle(4, 3, 3)
  };
  auto solution = OptimalRectanglePacking(input).compute();

  EXPECT_EQ(88, solution.first.getArea())
    << solutionToString(solution.first,
                        input,
                        solution.second);
}

TEST(OptimalRectanglePacking, Constant100)
{
  auto input = createSameRectangles(100);
  auto solution = OptimalRectanglePacking(input).compute();

  EXPECT_EQ(200, solution.first.getArea())
    << solutionToString(solution.first,
                        input,
                        solution.second);;
}

TEST(OptimalRectanglePacking, DISABLED_Square10)
{
  auto input = createDecrementingSquares(10);
  auto solution = OptimalRectanglePacking(input).compute();

  EXPECT_EQ(15*27, solution.first.getArea())
    << solutionToString(solution.first,
                        input,
                        solution.second);;
}

TEST(OptimalRectanglePacking, DISABLED_Rectangle10)
{
  std::vector<Rectangle> input = createDecrementingRectangles(10);

  EXPECT_EQ(OptimalRectanglePacking(input).compute().first.getArea(), 17*26);
}
