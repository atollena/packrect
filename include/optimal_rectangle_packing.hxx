#ifndef PACKING_MIN_AREA_HPP
#define PACKING_MIN_AREA_HPP

#include <vector>

namespace packing {
  class Rectangle;
  class RectanglePosition;
  class BoundingBox;
  
  class OptimalRectanglePacking {
  public:
    typedef std::pair<BoundingBox,
                      std::vector<RectanglePosition>> Packing;

    OptimalRectanglePacking(const std::vector<Rectangle> input);
    Packing compute () const;
  private:
    std::vector<Rectangle> input;
  };
}

#endif // PACKING_MIN_AREA_HPP
