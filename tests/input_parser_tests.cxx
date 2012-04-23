#include "gtest/gtest.h"
#include <sstream>

#include "input_parser.hxx"
#include "rectangle.hxx"

using namespace packing;

TEST(InputParser, SiteExample)
{
  std::stringstream input;
  input << "3\n8 8\n3 4\n4 3\n";

  std::vector<Rectangle> expectedResult = {
    Rectangle(8, 8, false),
    Rectangle(4, 3, true),
    Rectangle(4, 3, true)
  };

  auto result = parseInput(input);

  EXPECT_EQ(expectedResult, result);
}
