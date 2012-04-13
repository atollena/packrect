#include <assert.h>

#include "rectangle.hxx"

namespace packing {
  Rectangle::Rectangle(int width, int height)
    : width(width), height(height)
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

  bool Rectangle::BiggerWidth::operator()(const Rectangle & first,
                                          const Rectangle & second) const
  {
    return first.width > second.width;
  }
}
