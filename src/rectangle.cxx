#include "rectangle.hxx"

namespace packing {

  Rectangle::Rectangle(int height, int width)
    : height(height), width(width)
  {}

  Rectangle::Rectangle(const Rectangle & other)
    : height(other.height), width(other.width)
  {}

  Rectangle::~Rectangle () {}

  Rectangle& Rectangle::operator= (const Rectangle & other)
  {
    // Handles self assignment gratefully
    height = other.height;
    width = other.width;
    return *this;
  }
}
