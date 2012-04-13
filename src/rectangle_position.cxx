#include "rectangle_position.hxx"

namespace packing {
  RectanglePosition::RectanglePosition(int x, int y)
    :x(x), y(y){}

  bool RectanglePosition::operator==(const RectanglePosition& other) const
  {
    return other.x == x && other.y == y;
  }

  int RectanglePosition::getX() const { return x; }

  int RectanglePosition::getY() const { return y; }
}
