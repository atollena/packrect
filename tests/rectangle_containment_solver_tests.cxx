#include <algorithm>

#include "gtest/gtest.h"

#include "rectangle_containment_solver.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"

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
    RectanglePosition(Point(8, 3), true)
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

TEST(RectangleContainmentSolver, Square10)
{
  std::vector<Rectangle> input;
  for(int i = 1; i <= 10; i++) {
    input.push_back(Rectangle(i, i, i));
  }

  // Bouding box one size too small
  auto result = RectangleContainmentSolver(input, BoundingBox(26, 15)).compute();

  EXPECT_TRUE(result.empty());

  result = RectangleContainmentSolver(input, BoundingBox(27, 15)).compute();

  EXPECT_FALSE(result.empty());
}

TEST(RectangleContainmentSolver, Rectangle10_tooSmall)
{
  std::vector<Rectangle> input;
  for(int i = 0; i < 10; i++) {
    input.push_back(Rectangle(i + 1, i, i));
  }

  // Bouding box one size too small
  auto result = RectangleContainmentSolver(input, BoundingBox(26, 16)).compute();

  EXPECT_TRUE(result.empty());
}

TEST(RectangleContainmentSolver, Rectangle10)
{
  std::vector<Rectangle> input;
  for(int i = 0; i < 10; i++) {
    input.push_back(Rectangle(i + 1, i, i));
  }

  auto result = RectangleContainmentSolver(input, BoundingBox(26, 17)).compute();

  EXPECT_FALSE(result.empty());
}
