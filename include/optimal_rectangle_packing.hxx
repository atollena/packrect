#ifndef PACKING_MIN_AREA_HPP
#define PACKING_MIN_AREA_HPP

#include <list>
#include <deque>
#include <vector>

#include "solution.hxx"

namespace packing {
  class Rectangle;
  class RectanglePosition;

  Solution optimalRectanglePacking(const std::vector<Rectangle> & input);
}

#endif // PACKING_MIN_AREA_HPP
