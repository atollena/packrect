#ifndef WASTED_SPACE_PRUNER_HXX
#define WASTED_SPACE_PRUNER_HXX

#include <vector>
#include <deque>

#include "box_occupation_matrix.hxx"

namespace packing {
  class BoxOccupationMatrix;
  
  class WastedSpacePruner {
  public:
    bool operator() (const RectangleSize & boxSize,
                     const BoxOccupationMatrix & occupationMatrix,
                     std::vector<Rectangle>::const_iterator first,
                     std::vector<Rectangle>::const_iterator last,
                     int totalRectanglesArea) const;
  };
}

#endif
