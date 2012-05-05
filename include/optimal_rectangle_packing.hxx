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

    OptimalRectanglePacking(const std::vector<Rectangle> & input);
    Packing compute ();
  private:
    std::vector<Rectangle> input;

    std::list<RectanglePosition>
    solveRectangleContainment(const RectangleSize & boxSize);

    std::deque<RectangleSize> candidateBoxSizes() const;
    RectangleSize greedyRectanglePacker() const;

#ifdef STATISTICS
    int backtrackNodes;
#endif
  };
}

#endif // PACKING_MIN_AREA_HPP
