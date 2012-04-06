#ifndef PACKING_MIN_AREA_HPP
#define PACKING_MIN_AREA_HPP

#include <vector>

namespace packing {
  class Rectangle;
  
  class OptimalRectanglePacking {
  public:
    OptimalRectanglePacking(const std::vector<Rectangle>& input);    
    int compute () const;
  private:
    const std::vector<Rectangle>& input;
  };
}

#endif // PACKING_MIN_AREA_HPP
