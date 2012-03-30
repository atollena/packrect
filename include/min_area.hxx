#ifndef PACKING_MIN_AREA_HPP
#define PACKING_MIN_AREA_HPP

#include <vector>

namespace packing {
  class Rectangle;
  
  class MinArea {
  public:
    MinArea(const std::vector<Rectangle>& input);    
    int compute () const;
  private:
    const std::vector<Rectangle>& input;
  };
}

#endif // PACKING_MIN_AREA_HPP
