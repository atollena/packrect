#include "rectangle_position.hxx"

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
}
