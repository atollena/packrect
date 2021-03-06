#include "gtest/gtest.h"

#include "tests_helpers.hxx"
#include "rectangle.hxx"
#include "optimal_rectangle_packing.hxx"
#include "rectangle_containment_solver.hxx"
#include "solution_to_string.hxx"

using namespace packing;

class OptimalRectanglePackingTests : public testing::Test {
protected:
  void check(const std::vector<Rectangle> & input,
             int expectedArea)
  {
    auto solution = optimalRectanglePacking(input);

    EXPECT_EQ(expectedArea, solution.boxSize.computeArea())
      << solutionToString(solution.boxSize,
                          solution.rectangles,
                          solution.rectanglePositions);
  }
};

TEST_F(OptimalRectanglePackingTests, SiteExample)
{
  auto input = {
    Rectangle(8, 8, 1),
    Rectangle(4, 3, 2),
    Rectangle(4, 3, 3)
  };
  check(input, 88);
}

TEST_F(OptimalRectanglePackingTests, Square5)
{
  check(createDecrementingSquares(5), 5*12);
}

TEST_F(OptimalRectanglePackingTests, Square9)
{
  check(createDecrementingSquares(9), 15*20);
}

TEST_F(OptimalRectanglePackingTests, Constant100)
{
  check(createSameRectangles(100), 200);
}

TEST_F(OptimalRectanglePackingTests, DISABLED_Square14)
{
  check(createDecrementingSquares(14), 23*45);
}

TEST_F(OptimalRectanglePackingTests, DISABLED_Rectangle14)
{
  check(createDecrementingRectangles(14), 28*40);
}
