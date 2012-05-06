#include "wasted_space_pruner.hxx"

#include <deque>
#include <algorithm>

namespace packing {
  namespace {
    /**
     * Try to add `toAdd` to position container[index].  If container
     * capacity is too small, first increase its size.
     */
    void increase(std::deque<int> & container,
                  unsigned int index,
                  int toAdd)
    {
      if(container.size() <= index) {
        container.resize(index + 1);
      }
      container[index] += toAdd;
    }

    /**
     * Construct the list of bins capacities by looking at free
     * contiguous area vertically and horizontally on each free cell,
     * picking the smallest value as a result.
     */
    std::deque<int>
    constructBinsCapacities (const RectangleSize & boxSize,
                             const BoxOccupationMatrix & occupationMatrix)
    {
      std::deque<int> result;
      for(int j = 0; j < boxSize.height; ++j) {
        for(int i = 0; i < boxSize.width; ++i) {
          int binSize = occupationMatrix.minContiguousFreeCells(Point(i, j));
          increase(result, binSize, 1);
        }
      }
      return result;
    }

    /**
     * Construct the list of elements to pack by looking at the
     * smallest dimension of each remaining rectangle and adding its
     * area to the elements to pack.
     */
    std::deque<int>
    constructElements (std::vector<Rectangle>::const_iterator first,
                       std::vector<Rectangle>::const_iterator last)
    {
      std::deque<int> result;
      for(auto iter = first; iter != last; ++iter) {
        unsigned int minDimension = std::min(iter->getW(), iter->getH());
        increase(result, minDimension, iter->getArea());
      }
      return result;
    }

    /**
     * Computes the minimum wasted space in linear time.
     */
    int computeWastedSpace(const std::deque<int> & binCapacities,
                           const std::deque<int> & elements)
    {
      int wastedSpace = 0;
      int carryOver = 0;
      for(unsigned int i = 1;
          i < binCapacities.size() && i < elements.size();
          ++i) {
        if(binCapacities[i] > elements[i] + carryOver) {
          // All elements of smaller size fit in this bin, and there
          // is some unused capacity.
          wastedSpace += binCapacities[i] - elements[i] - carryOver;
          carryOver = 0;
        }
        else if(binCapacities[i] == elements[i] + carryOver) {
          // All elements fit exactly in the bin. No wasted space
          carryOver = 0;
        }
        else {
          // Some elements remain after filling the bin. Carry them
          // over to the next bin
          carryOver = carryOver + elements[i] - binCapacities[i];
        }
      }
      return wastedSpace;
    }
  }

  bool WastedSpacePruner::operator() (const RectangleSize & boxSize,
                                      const BoxOccupationMatrix & occupationMatrix,
                                      std::vector<Rectangle>::const_iterator first,
                                      std::vector<Rectangle>::const_iterator last,
                                      int totalRectanglesArea) const
  {
    std::deque<int> binCapacities = constructBinsCapacities(boxSize, occupationMatrix);

    std::deque<int> elements = constructElements(first, last);

    int wastedSpace = computeWastedSpace(binCapacities, elements);

    // If wasted space added to the sum of all rectangle areas exceeds
    // the size of the bounding box, we can't possibly have a
    // solution. Backtrack.
    return wastedSpace + totalRectanglesArea > boxSize.computeArea();
  }
}
