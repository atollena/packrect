#include "rectangle_position.hxx"

#include "rectangle.hxx"

namespace packing {
  RectanglePosition::RectanglePosition(Point leftBottom, bool vertical)
    :leftBottom(leftBottom), vertical(vertical)
  {}

  bool RectanglePosition::operator==(const RectanglePosition& other) const
  {
    return leftBottom == other.leftBottom && other.vertical == vertical;
  }

  Point RectanglePosition::getLeftBottom() const { return leftBottom; }

  int RectanglePosition::getLeftBottomX() const { return leftBottom.getX(); }

  int RectanglePosition::getLeftBottomY() const { return leftBottom.getY(); }

  bool RectanglePosition::isVertical() const { return vertical; }

  Point RectanglePosition::getTopRight(const Rectangle & rectangle) const
  {
    return leftBottom + Point(getHorizontalSize(rectangle) - 1,
                              getVerticalSize(rectangle) - 1);
  }

  Point RectanglePosition::getTopLeft(const Rectangle & rectangle) const
  {
    return leftBottom + Point(0, getVerticalSize(rectangle) - 1);
  }

  Point RectanglePosition::getBottomRight(const Rectangle & rectangle) const
  {
    return leftBottom + Point(getHorizontalSize(rectangle) - 1, 0);
  }

  std::vector<Point> RectanglePosition::getTopLine(const Rectangle & rectangle) const
  {
    std::vector<Point> result;

    return getLine(rectangle, LineType::TOP);
  }

  std::vector<Point> RectanglePosition::getBottomLine(const Rectangle & rectangle) const
  {
    std::vector<Point> result;

    return getLine(rectangle, LineType::BOTTOM);
  }

  std::vector<Point> RectanglePosition::getLeftLine(const Rectangle & rectangle) const
  {
    std::vector<Point> result;

    return getLine(rectangle, LineType::LEFT);
  }

  std::vector<Point> RectanglePosition::getRightLine(const Rectangle & rectangle) const
  {
    std::vector<Point> result;

    return getLine(rectangle, LineType::RIGHT);
  }

  std::vector<Point> RectanglePosition::getLine(const Rectangle & rectangle,
                                                const LineType & lineType) const
  {
    std::vector<Point> result;
    switch(lineType) {
    case LineType::LEFT:
      result.reserve(getVerticalSize(rectangle));
      for(int x = 0; x < getVerticalSize(rectangle); x++) {
        result.push_back(getLeftBottom() + Point(0, x));
      }
      break;
    case LineType::RIGHT:
      result.reserve(getVerticalSize(rectangle));
      for(int x = 0; x < getVerticalSize(rectangle); x++) {
        result.push_back(getBottomRight(rectangle) + Point(0, x));
      }
      break;
    case LineType::TOP:
      result.reserve(getHorizontalSize(rectangle));
      for(int x = 0; x < getHorizontalSize(rectangle); x++) {
        result.push_back(getTopLeft(rectangle) + Point(x, 0));
      }
      break;
    case LineType::BOTTOM:
      result.reserve(getHorizontalSize(rectangle));
      for(int x = 0; x < getHorizontalSize(rectangle); x++) {
        result.push_back(getLeftBottom() + Point(x, 0));
      }
      break;
    }
    return result;
  }

  int RectanglePosition::getHorizontalSize(const Rectangle & rectangle) const
  {
    if(isVertical()) {
      return rectangle.getH();
    }
    else {
      return rectangle.getW();
    }
  }

  int RectanglePosition::getVerticalSize(const Rectangle & rectangle) const
  {
    if(isVertical()) {
      return rectangle.getW();
    }
    else {
      return rectangle.getH();
    }
  }

  std::vector<Point> RectanglePosition::getSides(const Rectangle & rectangle) const
  {
    int rectangleWidth = rectangle.getW();
    int rectangleHeight = rectangle.getH();

    if(isVertical()) {
      std::swap(rectangleWidth, rectangleHeight);
    }

    std::vector<Point> result;
    result.reserve(rectangleWidth * 2 + rectangleHeight * 2 - 4);

    for(int x = 0; x < rectangleWidth; x++) {
      result.push_back(getLeftBottom() + Point(x, 0));
      result.push_back(getLeftBottom() + Point(x, rectangleHeight - 1));
    }
    for(int y = 1; y < rectangleHeight - 1; y++) {
      result.push_back(getLeftBottom() + Point(0, y));
      result.push_back(getLeftBottom() + Point(rectangleWidth - 1, y));
    }
    return result;
  }
}
