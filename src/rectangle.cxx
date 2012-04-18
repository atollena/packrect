#include <cassert>

#include "rectangle.hxx"

namespace packing {
  Rectangle::Rectangle(int width, int height, RectangleId id)
    : id(id), width(width), height(height)
  {
    // Check that we meet the class requirements
    assert(width >= height);
  }

  Rectangle::Rectangle(const Rectangle & other)
    : width(other.width), height(other.height)
  {}

  Rectangle::~Rectangle () {}

  Rectangle& Rectangle::operator= (const Rectangle & other)
  {
    // Handles self assignment gratefully
    height = other.height;
    width = other.width;
    return *this;
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
    return first.width > second.width;
  }
}
