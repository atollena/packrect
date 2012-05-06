#include "gtest/gtest.h"

#include <algorithm>

#include "bounding_box.hxx"
#include "box_occupation_matrix.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"

using namespace packing;

class BoxOccupationMatrixTests : public testing::Test {
protected:
  static const int WIDTH = 30;
  static const int HEIGHT = 15;

  Rectangle rectangle_exemple;
  RectanglePosition position_exemple;
  BoxOccupationMatrix testBox;
  RectangleId rectangleExempleId;


  BoxOccupationMatrixTests()
    : rectangle_exemple(5, 3, 0),
      position_exemple(Point(9, 4), false),
      testBox(RectangleSize(WIDTH, HEIGHT)),
      rectangleExempleId(0)
  {}

  virtual void SetUp()
  {
    testBox.set(rectangle_exemple,
                position_exemple);
  }

  // Let's define some positions we'd like to check
  Point ExampleRectangleBottomLeft() {
    return position_exemple.getLeftBottom();
  }

  Point ExampleRectangleMiddle() {
    return Point(position_exemple.getLeftBottomX()
                             + rectangle_exemple.getW() / 2,
                             position_exemple.getLeftBottomY()
                             + rectangle_exemple.getH() / 2);
  }
  Point ExampleRectangleTopRight() {
    return Point(position_exemple.getLeftBottomX()
                             + rectangle_exemple.getW() - 1,
                             position_exemple.getLeftBottomY()
                             + rectangle_exemple.getH() - 1);
  }
  Point ExampleRectangleBottomLeftOutside() {
    return Point(position_exemple.getLeftBottomX() - 1,
                             position_exemple.getLeftBottomY());
  }
  Point ExampleRectangleTopRightOutside() {
    return Point(position_exemple.getLeftBottomX()
                             + rectangle_exemple.getW(),
                             position_exemple.getLeftBottomY()
                             + rectangle_exemple.getH() + 1);
  }

  Point BottomLeftCorner() {
    return Point(0, 0);
  }
  Point TopRightCorner() {
    return Point(WIDTH - 1, HEIGHT - 1);
  }
};

TEST_F(BoxOccupationMatrixTests, Query)
{
  EXPECT_EQ(rectangleExempleId,
            testBox.query(position_exemple.getLeftBottom())) << testBox;
  EXPECT_EQ(rectangleExempleId,
            testBox.query(ExampleRectangleTopRight())) << testBox;
  EXPECT_EQ(rectangleExempleId,
            testBox.query(ExampleRectangleMiddle())) << testBox;

  EXPECT_EQ(-1, testBox.query(BottomLeftCorner())) << testBox;
  EXPECT_EQ(-1, testBox.query(TopRightCorner())) << testBox;

  EXPECT_EQ(-1, testBox.query(ExampleRectangleBottomLeftOutside())) << testBox;
  EXPECT_EQ(-1, testBox.query(ExampleRectangleTopRightOutside())) << testBox;
}

TEST_F(BoxOccupationMatrixTests, Unset)
{
  testBox.unset(rectangle_exemple, position_exemple);

  EXPECT_EQ(-1, testBox.query(ExampleRectangleBottomLeft())) << testBox;
  EXPECT_EQ(-1, testBox.query(ExampleRectangleTopRight())) << testBox;
  EXPECT_EQ(-1, testBox.query(ExampleRectangleMiddle())) << testBox;
}

TEST_F(BoxOccupationMatrixTests, SetVertical)
{
  static const int rectangle_id = 12;
  testBox.set(Rectangle(5, 3, rectangle_id),
              RectanglePosition(Point(0, 0), true));

  EXPECT_EQ(rectangle_id, testBox.query(BottomLeftCorner())) << testBox;
  EXPECT_EQ(-1, testBox.query(Point(4, 2))) << testBox;
  EXPECT_EQ(rectangle_id, testBox.query(Point(2, 4))) << testBox;
}

TEST_F(BoxOccupationMatrixTests, minContiguousFreeCells)
{
  testBox.set(Rectangle(9, 4, 1), RectanglePosition(Point(0, 0), false));
  testBox.unset(Rectangle(9, 4, 1), RectanglePosition(Point(0, 0), false));

  auto result = testBox.minContiguousFreeCells();

  EXPECT_EQ((unsigned int) 16, result.size()) << testBox;
  EXPECT_EQ(RectangleSize(WIDTH, HEIGHT).computeArea(),
            std::accumulate(result.begin(), result.end(), 0));

  EXPECT_EQ(0, result[1]) << testBox;
  EXPECT_EQ(0, result[2]) << testBox;
  EXPECT_EQ(0, result[3]) << testBox;
  EXPECT_EQ(20, result[4]) << testBox;
  EXPECT_EQ(0, result[5]) << testBox;
  EXPECT_EQ(0, result[6]) << testBox;
  EXPECT_EQ(0, result[7]) << testBox;
  EXPECT_EQ(40, result[8]) << testBox;
  EXPECT_EQ(27, result[9]) << testBox;
  EXPECT_EQ(0, result[10]) << testBox;
  EXPECT_EQ(0, result[11]) << testBox;
  EXPECT_EQ(0, result[12]) << testBox;
  EXPECT_EQ(0, result[13]) << testBox;
  EXPECT_EQ(0, result[14]) << testBox;
  EXPECT_EQ(348, result[15]) << testBox;
}

TEST_F(BoxOccupationMatrixTests, minContiguousFreeCellsTwoRects)
{
  testBox.set(Rectangle(9, 4, 1), RectanglePosition(Point(15, 5), false));
  testBox.set(Rectangle(5, 2, 2), RectanglePosition(Point(10, 7), false));
  testBox.set(Rectangle(8, 3, 3), RectanglePosition(Point(7, 10), false));

  auto result = testBox.minContiguousFreeCells();

  EXPECT_EQ((unsigned int) 16, result.size()) << testBox;
  EXPECT_EQ(RectangleSize(WIDTH, HEIGHT).computeArea(),
            std::accumulate(result.begin(), result.end(), 0));

  EXPECT_EQ(7, result[1]) << testBox;
  EXPECT_EQ(16, result[2]) << testBox;
  EXPECT_EQ(3, result[3]) << testBox;
  EXPECT_EQ(20, result[4]) << testBox;
  EXPECT_EQ(45, result[5]) << testBox;
  EXPECT_EQ(54 + 24, result[6]) << testBox;
  EXPECT_EQ(26, result[7]) << testBox;
  EXPECT_EQ(0, result[8]) << testBox;
  EXPECT_EQ(27, result[9]) << testBox;
  EXPECT_EQ(28, result[10]) << testBox;
  EXPECT_EQ(0, result[11]) << testBox;
  EXPECT_EQ(0, result[12]) << testBox;
  EXPECT_EQ(0, result[13]) << testBox;
  EXPECT_EQ(0, result[14]) << testBox;
  EXPECT_EQ(115, result[15]) << testBox;
}
