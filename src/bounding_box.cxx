#include "bounding_box.hxx"

namespace packing {
  BoundingBox::BoundingBox(int width, int height)
    :width(width), height(height){}

  int BoundingBox::area() const
  {
    return width*height;
  }
}
