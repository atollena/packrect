#include <cassert>

#include "rectangle.hxx"
#include "rectangle_position.hxx"

namespace packing {
  Rectangle::Rectangle(int width, int height, RectangleId id)
    : id(id), width(width), height(height)
  {
    // Check that we meet the class requirements
    assert(width >= height);
  }

  bool Rectangle::operator== (const Rectangle & other) const
  {
    return other.width == width && other.height == height;
  }

  int Rectangle::getH() const
  {
    return height;
  }

  int Rectangle::getW() const
  {
    return width;
  }

  RectangleId Rectangle::getId() const
  {
    return id;
  }

  bool Rectangle::isSquare() const
  {
    return width == height;
  }

  bool Rectangle::BiggerWidth::operator()(const Rectangle & first,
                                          const Rectangle & second) const
  {
    return first.getW() > second.getW();
  }

  bool Rectangle::BiggerHeight::operator()(const Rectangle & first,
                                           const Rectangle & second) const
  {
    return first.getH() > second.getH();
  }
}
