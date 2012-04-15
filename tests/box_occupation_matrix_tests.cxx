#include "gtest/gtest.h"

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
    : rectangle_exemple(5, 3),
      position_exemple(Point(9, 4), false),
      testBox(BoundingBox(WIDTH, HEIGHT)),
      rectangleExempleId(0)
  {}

  virtual void SetUp()
  {
    testBox.set(rectangle_exemple,
                position_exemple,
                rectangleExempleId);
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
  testBox.set(Rectangle(5, 3),
              RectanglePosition(Point(0, 0), true),
              rectangle_id);

  EXPECT_EQ(rectangle_id, testBox.query(BottomLeftCorner())) << testBox;
  EXPECT_EQ(-1, testBox.query(Point(4, 2))) << testBox;
  EXPECT_EQ(rectangle_id, testBox.query(Point(2, 4))) << testBox;
}
