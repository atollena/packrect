#include "rectangle_size.hxx"

namespace packing {

  RectangleSize::RectangleSize(int width, int height)
    :width(width), height(height)
  {}

  int RectangleSize::computeArea() const
  {
    return width * height;
  }

  bool RectangleSize::SmallerArea::operator()(const RectangleSize & first,
                                              const RectangleSize & second) const
  {
    return first.computeArea() < second.computeArea();
  }
}
