#include <sstream>

#include "gtest/gtest.h"

#include "bounding_box.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "solution_to_string.hxx"

using namespace packing;

TEST(SolutionToString, Trivial1)
{
  const std::vector<Rectangle> rectangles = {
    Rectangle(8, 8, 1),
  };

  std::list<RectanglePosition> positions = {
    RectanglePosition(Point(0, 0), false),
  };

  std::stringstream expected;
  expected << "+------+" << std::endl
           << "|      |" << std::endl
           << "|      |" << std::endl
           << "|      |" << std::endl
           << "|      |" << std::endl
           << "|      |" << std::endl
           << "|      |" << std::endl
           << "+------+" << std::endl;

  std::string result = solutionToString(RectangleSize(8, 8),
                                        rectangles,
                                        positions);

  EXPECT_EQ(expected.str(),
            result) << result;
}

TEST(SolutionToString, TrivialVertical)
{
  const std::vector<Rectangle> rectangles = {
    Rectangle(4, 3, 1),
  };

  std::list<RectanglePosition> positions = {
    RectanglePosition(Point(0, 0), true),
  };

  std::stringstream expected;
  expected << "+-+" << std::endl
           << "| |" << std::endl
           << "| |" << std::endl
           << "+-+" << std::endl;

  std::string result = solutionToString(RectangleSize(3, 4),
                                        rectangles,
                                        positions);

  EXPECT_EQ(expected.str(),
            result) << result;
}

TEST(SolutionToString, TrivialHorizontal)
{
  const std::vector<Rectangle> rectangles = {
    Rectangle(4, 3, 1),
  };

  std::list<RectanglePosition> positions = {
    RectanglePosition(Point(0, 0), false),
  };

  std::stringstream expected;
  expected << "+--+" << std::endl
           << "|  |" << std::endl
           << "+--+" << std::endl;

  std::string result = solutionToString(RectangleSize(4, 3),
                                        rectangles,
                                        positions);

  EXPECT_EQ(expected.str(),
            result) << result;
}

TEST(SolutionToString, SiteExample)
{
  const std::vector<Rectangle> rectangles = {
    Rectangle(8, 8, 1),
    Rectangle(4, 3, 2),
    Rectangle(4, 3, 3)
  };

  std::list<RectanglePosition> positions = {
    RectanglePosition(Point(0, 0), false),
    RectanglePosition(Point(8, 0), true),
    RectanglePosition(Point(8, 4), true)
  };

  std::stringstream expected;
  expected << "+------++-+" << std::endl
           << "|      || |" << std::endl
           << "|      || |" << std::endl
           << "|      |+-+" << std::endl
           << "|      |+-+" << std::endl
           << "|      || |" << std::endl
           << "|      || |" << std::endl
           << "+------++-+" << std::endl;


  std::string result = solutionToString(RectangleSize(11, 8),
                                        rectangles,
                                        positions);

  EXPECT_EQ(expected.str(),
            result) << result;
}
