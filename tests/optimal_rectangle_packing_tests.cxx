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
    auto solution = OptimalRectanglePacking(input).compute();

    EXPECT_EQ(expectedArea, solution.first.computeArea())
      << solutionToString(solution.first,
                          input,
                          solution.second);
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

TEST_F(OptimalRectanglePackingTests, Square10)
{
  check(createDecrementingSquares(10), 15*27);
}

TEST_F(OptimalRectanglePackingTests, Rectangle10)
{
  check(createDecrementingRectangles(10), 17*26);
}
