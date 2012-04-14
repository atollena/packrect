#include "gtest/gtest.h"

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
      position_exemple(9, 4),
      testBox(WIDTH, HEIGHT),
      rectangleExempleId(0)
  {}

  virtual void SetUp()
  {
    testBox.set(rectangle_exemple,
                position_exemple,
                rectangleExempleId);
  }

  // Let's define some positions we'd like to check
  RectanglePosition ExampleRectangleBottomLeft() {
    return RectanglePosition(position_exemple);
  }

  RectanglePosition ExampleRectangleMiddle() {
    return RectanglePosition(position_exemple.getX() + rectangle_exemple.getW() / 2,
                             position_exemple.getY() + rectangle_exemple.getH() / 2);
  }
  RectanglePosition ExampleRectangleTopRight() {
    return RectanglePosition(position_exemple.getX() + rectangle_exemple.getW() - 1,
                             position_exemple.getY() + rectangle_exemple.getH() - 1);
  }
  RectanglePosition ExampleRectangleBottomLeftOutside() {
    return RectanglePosition(position_exemple.getX() - 1,
                             position_exemple.getY());
  }
  RectanglePosition ExampleRectangleTopRightOutside() {
    return RectanglePosition(position_exemple.getX() + rectangle_exemple.getW(),
                             position_exemple.getY() + rectangle_exemple.getH() + 1);
  }

  RectanglePosition BottomLeftCorner() {
    return RectanglePosition(0, 0);
  }
  RectanglePosition TopRightCorner() {
    return RectanglePosition(WIDTH - 1, HEIGHT - 1);
  }
};

TEST_F(BoxOccupationMatrixTests, Query)
{
  EXPECT_EQ(rectangleExempleId, testBox.query(position_exemple)) << testBox;
  EXPECT_EQ(rectangleExempleId, testBox.query(ExampleRectangleTopRight())) << testBox;
  EXPECT_EQ(rectangleExempleId, testBox.query(ExampleRectangleMiddle())) << testBox;

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

TEST_F(BoxOccupationMatrixTests, Set)
{
  static const int rectangle_id = 12;
  testBox.set(Rectangle(5, 3), RectanglePosition(0,0), rectangle_id);

  EXPECT_EQ(rectangle_id, testBox.query(BottomLeftCorner())) << testBox;
}
