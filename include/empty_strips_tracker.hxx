#ifndef EMPTY_STRIPS_TRACKER_HXX
#define EMPTY_STRIPS_TRACKER_HXX

#include <deque>
#include <vector>

namespace packing {
  class BoxOccupationMatrix;
  
  class EmptyStripsTracker {
  public:
    EmptyStripsTracker(const BoxOccupationMatrix & occupationMatrix);
    
    void recomputeEmptyStrips(int positionX,
                              int positionY,
                              int rectangleWidth,
                              int rectangleHeight);
    /**
     * See definition in BoxOccupationMatrix.
     */
    std::deque<int> minContiguousFreeCells() const;
    
  private:
    const BoxOccupationMatrix & occupationMatrix;

    /**
     * Keeps track of vertical empty strips
     */
    std::vector<std::vector<int>> verticalEmptyStrips;

    /**
     * Keeps track of horizontal empty strips
     */
    std::vector<std::vector<int>> horizontalEmptyStrips;
  };
}

#endif
