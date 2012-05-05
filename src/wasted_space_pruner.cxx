#include "wasted_space_pruner.hxx"

#include <deque>
#include <algorithm>

namespace packing {
  bool WastedSpacePruner::operator() (const RectangleSize & boxSize,
                                      const BoxOccupationMatrix & occupationMatrix,
                                      std::vector<Rectangle>::const_iterator first,
                                      std::vector<Rectangle>::const_iterator last,
                                      int totalRectanglesArea) const
  {
    /* Construct bins areas */
    std::deque<int> areaAvailableForBinSize;
    unsigned int maxBinSize = 0;
    for(int j = 0; j < boxSize.height; ++j) {
      for(int i = 0; i < boxSize.width; ++i) {
        unsigned int binSize = occupationMatrix.minContiguousFreeCells(Point(i, j));
        if(binSize > areaAvailableForBinSize.size()) {
          areaAvailableForBinSize.resize(binSize + 1);
        }
        ++(areaAvailableForBinSize[binSize]);
        if(binSize > maxBinSize) {
          maxBinSize = binSize;
        }
      }
    }

    /* Construct elements to pack in the bin */
    std::deque<int> elements;
    for(auto iter = first;
        iter != last;
        iter++) {
      unsigned int minDimension = std::min(iter->getW(), iter->getH());
      if(minDimension > elements.size()) {
        elements.resize(minDimension + 1);
      }
      elements[minDimension] += iter->getArea();
    }
    
    /* See how much wasted space we have */
    int wastedSpace = 0;
    int carryOver = 0;
    for(unsigned int i = 1; i < areaAvailableForBinSize.size(); ++i) {
      elements[i] += carryOver;
      if(areaAvailableForBinSize[i] > elements[i]) {
        wastedSpace += areaAvailableForBinSize[i] - elements[i];
        carryOver = 0;
      }
      else if(areaAvailableForBinSize[i] == elements[i]) {
        carryOver = 0;
      }
      else {
        carryOver = elements[i] - areaAvailableForBinSize[i];
      }
    }
      
    /* Check if remaining area  */
    if(wastedSpace + totalRectanglesArea > boxSize.computeArea()) {
      return true;
    }

    return false;
  }
}
