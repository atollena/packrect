#ifndef PACKING_MIN_AREA_HPP
#define PACKING_MIN_AREA_HPP

#include <list>
#include <deque>
#include <vector>

#include "rectangle_size.hxx"

namespace packing {
  class Rectangle;
  class RectanglePosition;
  
  class OptimalRectanglePacking {
  public:
    typedef std::pair<RectangleSize,
                      std::list<RectanglePosition>> Packing;

    OptimalRectanglePacking(const std::vector<Rectangle> input);
    Packing compute () const;
  private:
    std::vector<Rectangle> input;

    std::deque<RectangleSize> candidateBoxSizes() const;
    RectangleSize greedyRectanglePacker() const;
  };
}

#endif // PACKING_MIN_AREA_HPP
