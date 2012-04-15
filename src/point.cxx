#include "point.hxx"

namespace packing {

  Point::Point(int x, int y)
    :x(x), y(y)
  {}

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  int Point::getX() const { return x; }
  int Point::getY() const { return y; }
}
