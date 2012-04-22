#ifndef PACKING_MIN_AREA_HPP
#define PACKING_MIN_AREA_HPP

#include <list>
#include <deque>
#include <vector>

namespace packing {
  class Rectangle;
  class RectanglePosition;
  class BoundingBox;
  
  class OptimalRectanglePacking {
  public:
    typedef std::pair<BoundingBox,
                      std::list<RectanglePosition>> Packing;

    OptimalRectanglePacking(const std::vector<Rectangle> input);
    Packing compute () const;
  private:
    std::vector<Rectangle> input;

    std::deque<BoundingBox> candidateBoxes() const;
    BoundingBox greedyRectanglePacker() const;
  };
}

#endif // PACKING_MIN_AREA_HPP
