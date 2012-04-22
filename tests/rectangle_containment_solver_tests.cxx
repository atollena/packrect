#include <algorithm>

#include "gtest/gtest.h"

#include "tests_helpers.hxx"

#include "rectangle_containment_solver.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "solution_to_string.hxx"

using namespace packing;

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

  auto result = RectangleContainmentSolver(input, BoundingBox(11, 8)).compute();

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

TEST(RectangleContainmentSolver, SiteExampleBoundingBoxTooSmall)
{
  const std::vector<Rectangle> input = {
    Rectangle(8, 8, 1),
    Rectangle(4, 3, 2),
    Rectangle(4, 3, 3)
  };

  auto result = RectangleContainmentSolver(input, BoundingBox(10, 8)).compute();

  EXPECT_TRUE(result.empty());
}

TEST(RectangleContainmentSolver, Square5)
{
  std::vector<Rectangle> input = createDecrementingSquares(5);

  auto result = RectangleContainmentSolver(input, BoundingBox(12, 5)).compute();

  EXPECT_FALSE(result.empty());
}

TEST(RectangleContainmentSolver, Square7)
{
  std::vector<Rectangle> input = createDecrementingSquares(7);;

  auto result = RectangleContainmentSolver(input, BoundingBox(7, 22)).compute();

  EXPECT_FALSE(result.empty());
}

TEST(RectangleContainmentSolver, Square10_tooSmall)
{
  std::vector<Rectangle> input = createDecrementingSquares(10);

  // Bouding box one size too small
  auto box = BoundingBox(26, 15);
  auto result = RectangleContainmentSolver(input, box).compute();

  EXPECT_TRUE(result.empty()) << solutionToString(box, input, result);
}

TEST(RectangleContainmentSolver, Square10)
{
  std::vector<Rectangle> input = createDecrementingSquares(10);

  auto box = BoundingBox(27, 15);
  auto result = RectangleContainmentSolver(input, box).compute();

  EXPECT_FALSE(result.empty()) << solutionToString(box, input, result);
}

TEST(RectangleContainmentSolver, Rectangle10_tooSmall)
{
  std::vector<Rectangle> input = createDecrementingRectangles(10);

  // Bouding box one size too small
  auto result = RectangleContainmentSolver(input, BoundingBox(26, 16)).compute();

  EXPECT_TRUE(result.empty());
}

TEST(RectangleContainmentSolver, Rectangle10)
{
  std::vector<Rectangle> input = createDecrementingRectangles(10);

  auto result = RectangleContainmentSolver(input, BoundingBox(26, 17)).compute();

  EXPECT_FALSE(result.empty());
}
