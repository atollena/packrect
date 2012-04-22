#include "gtest/gtest.h"

#include "bounding_box.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"


using namespace packing;


class BoundingBoxTests : public testing::Test {
protected:
  BoundingBox emptyBox;
  BoundingBox halfFullBox;

  BoundingBoxTests()
    : emptyBox(10, 5), halfFullBox(10, 5)
  {
    halfFullBox.set(Rectangle(2, 2, 0),
                    RectanglePosition(Point(3, 0), false));
    halfFullBox.set(Rectangle(5, 1, 1),
                    RectanglePosition(Point(5, 4), false));
    /**
     * We just set the following layout
     * +----------+
     * |     xxxxx|
     * |          |
     * |          |
     * |xx        |
     * |xx        |
     * +----------+
     */

  }
};

TEST_F(BoundingBoxTests, candidatePositionsEmpty)
{
  Rectangle rectangle (11, 5, 3);
  EXPECT_TRUE(emptyBox.candidatePosition(rectangle).empty());
  EXPECT_TRUE(emptyBox.firstRectangleCandidatePosition(rectangle).empty());

  rectangle = Rectangle (10, 6, 3);
  EXPECT_TRUE(emptyBox.candidatePosition(rectangle).empty());
  EXPECT_TRUE(emptyBox.firstRectangleCandidatePosition(rectangle).empty());
}

TEST_F(BoundingBoxTests, candidatePositionsOnlyHorizontal)
{
  Rectangle rectangle (10, 5, 3);

  std::deque<RectanglePosition> positions =
    emptyBox.candidatePosition(rectangle);
  
  ASSERT_EQ((size_t) 1, positions.size());

  RectanglePosition position = positions.back();
  EXPECT_EQ(Point(0, 0), position.getLeftBottom());
  EXPECT_FALSE(position.isVertical());
}

TEST_F(BoundingBoxTests, firstRectangleCandidatePositionMultiple)
{
  Rectangle rectangle (3, 2, 3);

  std::vector<RectanglePosition> positions =
    emptyBox.firstRectangleCandidatePosition(rectangle);

  EXPECT_EQ((size_t) 30, positions.size());
}

TEST_F(BoundingBoxTests, firstRectangleCandidatePositionMultipleSquare)
{
  Rectangle square (2, 2, 3);

  std::vector<RectanglePosition> positions =
    emptyBox.firstRectangleCandidatePosition(square);

  EXPECT_EQ((size_t) 15, positions.size());
}

TEST_F(BoundingBoxTests, candidatePositionMultiple)
{
  Rectangle rectangle (3, 2, 3);

  std::deque<RectanglePosition> positions =
    halfFullBox.candidatePosition(rectangle);

  EXPECT_EQ((size_t) 35, positions.size());
}

TEST_F(BoundingBoxTests, candidatePositionMultipleSquare)
{
  Rectangle rectangle (2, 2, 3);

  std::deque<RectanglePosition> positions =
    halfFullBox.candidatePosition(rectangle);

  EXPECT_EQ((size_t) 25, positions.size());
}
