#include "gtest/gtest.h"

#include "wasted_space_pruner.hxx"

using namespace packing;

TEST(WastedSpacePrunerTests, Square6Pruned)
{
  auto boxSize = RectangleSize(12, 8);

  auto occupationMatrix = BoxOccupationMatrix(boxSize);
  occupationMatrix.set(Rectangle(6, 6, 6),
                       RectanglePosition(Point(0, 0), false));
  
  auto remainingInput = std::vector<Rectangle> {
    Rectangle(5, 5, 5),
    Rectangle(4, 4, 4),
    Rectangle(3, 3, 3),
    Rectangle(2, 2, 2),
    Rectangle(1, 1, 1)
  };

  EXPECT_TRUE(WastedSpacePruner()(boxSize,
                                  occupationMatrix,
                                  remainingInput.begin(),
                                  remainingInput.end(),
                                  boxSize.computeArea()));
}

TEST(WastedSpacePrunerTests, AllDone)
{
  auto boxSize = RectangleSize(1, 1);
  auto occupationMatrix = BoxOccupationMatrix(boxSize);

  auto remainingInput = std::vector<Rectangle> {
    Rectangle(1, 1, 1)
  };

  EXPECT_FALSE(WastedSpacePruner()(boxSize,
                                   occupationMatrix,
                                   remainingInput.begin(),
                                   remainingInput.end(),
                                   1));
}

TEST(WastedSpacePrunerTests, SiteExample)
{
  auto boxSize = RectangleSize(11, 8);

  auto occupationMatrix = BoxOccupationMatrix(boxSize);
  occupationMatrix.set(Rectangle(8, 8, 0),
                       RectanglePosition(Point(0, 0), true));
  occupationMatrix.set(Rectangle(4, 3, 1),
                       RectanglePosition(Point(8, 0), true));
  auto remainingInput = std::vector<Rectangle> {
    Rectangle(4, 3, 2)
  };

  EXPECT_FALSE(WastedSpacePruner()(boxSize,
                                   occupationMatrix,
                                   remainingInput.begin(),
                                   remainingInput.end(),
                                   1));
}
