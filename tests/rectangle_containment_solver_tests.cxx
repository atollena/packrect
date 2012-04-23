#include <algorithm>

#include "gtest/gtest.h"

#include "tests_helpers.hxx"

#include "rectangle_containment_solver.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "solution_to_string.hxx"

using namespace packing;

class RectangleContainmentSolverTests : public testing::Test {
protected:
  void checkHasSolution (const std::vector<Rectangle> & input,
                         const RectangleSize & boxSize)
  {
    auto result = RectangleContainmentSolver(input, boxSize).compute();
  
    EXPECT_FALSE(result.empty()) << solutionToString(boxSize, input, result);
  }

  void checkNoSolution(const std::vector<Rectangle> & input,
                       const RectangleSize & boxSize)
  {
    auto result = RectangleContainmentSolver(input, boxSize).compute();

    EXPECT_TRUE(result.empty()) << solutionToString(boxSize, input, result);
  }  
};



TEST(RectangleContainmentSolver, SiteExample)
{
  const std::vector<Rectangle> input = {
    Rectangle(8, 8, 1),
    Rectangle(4, 3, 2),
    Rectangle(4, 3, 3)
  };

  std::vector<RectanglePosition> expectedResult = {
    RectanglePosition(Point(0, 0), false),
    RectanglePosition(Point(8, 0), true),
    RectanglePosition(Point(8, 4), true)
  };

  auto size = RectangleSize(11, 8);
  auto result = RectangleContainmentSolver(input, size).compute();

  EXPECT_EQ(expectedResult.size(), result.size());

  // Check that each element in result is present in expectedResult
  for(auto position: result) {
    EXPECT_TRUE(std::find(expectedResult.begin(),
                          expectedResult.end(),
                          position) != expectedResult.end())
      << "position x=" << position.getLeftBottomX()
      << ", y=" << position.getLeftBottomY() << " not expected";
  }
}

TEST_F(RectangleContainmentSolverTests, Square5)
{
  checkHasSolution(createDecrementingSquares(5), RectangleSize(12, 5));
}

TEST_F(RectangleContainmentSolverTests, Square7)
{
  checkHasSolution(createDecrementingSquares(7), RectangleSize(7, 22));
}

TEST_F(RectangleContainmentSolverTests, Square10)
{
  checkHasSolution(createDecrementingSquares(10), RectangleSize(27, 15));
}

TEST_F(RectangleContainmentSolverTests, Rectangle10)
{
  checkHasSolution(createDecrementingRectangles(10), RectangleSize(26, 17));
}

TEST_F(RectangleContainmentSolverTests, Constant100)
{
  checkHasSolution(createSameRectangles(100), RectangleSize(200, 1));
}

TEST_F(RectangleContainmentSolverTests, SiteExampleBoundingBoxTooSmall)
{
  const std::vector<Rectangle> input = {
    Rectangle(8, 8, 1),
    Rectangle(4, 3, 2),
    Rectangle(4, 3, 3)
  };

  checkNoSolution(input, RectangleSize(10, 8));
}

TEST_F(RectangleContainmentSolverTests, Square10_tooSmall)
{
  checkNoSolution(createDecrementingSquares(10), RectangleSize(26, 15));
}

TEST_F(RectangleContainmentSolverTests, DISABLED_Rectangle10_tooSmall)
{
  checkNoSolution(createDecrementingRectangles(10), RectangleSize(26, 16));
}

TEST_F(RectangleContainmentSolverTests, DISABLED_Constant10_tooSmall)
{
  checkNoSolution(createSameRectangles(100), RectangleSize(199, 1));
}
