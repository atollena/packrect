#include "rectangle_size.hxx"

RectangleSize::RectangleSize(int width, int height)
  :width(width), height(height)
{}

int RectangleSize::computeArea() const
{
  return width * height;
}
