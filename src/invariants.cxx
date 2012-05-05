#include "invariants.hxx"

#include <algorithm>

namespace packing {
  Invariants::Invariants(const std::vector<Rectangle> & input)
    : input(input)
  {
    totalRectangleArea = std::accumulate(input.begin(),
                                         input.end(),
                                         0,
                                         [](int currentArea, const Rectangle & rectangle)
                                         {
                                           return currentArea + rectangle.getArea();
                                         });
  }
}
