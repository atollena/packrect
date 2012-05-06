#include "empty_strips_tracker.hxx"
#include "box_occupation_matrix.hxx"

namespace packing {
  EmptyStripsTracker::EmptyStripsTracker(const BoxOccupationMatrix & occupationMatrix)
    : occupationMatrix(occupationMatrix),
      verticalEmptyStrips(occupationMatrix.width,
                          std::vector<int>(occupationMatrix.height,
                                           occupationMatrix.height)),
      horizontalEmptyStrips(occupationMatrix.width,
                            std::vector<int>(occupationMatrix.height,
                                             occupationMatrix.width))
  {}


  std::deque<int> EmptyStripsTracker::minContiguousFreeCells() const
  {
    std::deque<int> result;
    for(unsigned int i = 0; i < verticalEmptyStrips.size(); ++i) {
      for(unsigned int j = 0; j < verticalEmptyStrips[i].size(); ++j) {
        unsigned int toInsert = std::min(verticalEmptyStrips[i][j],
                                         horizontalEmptyStrips[i][j]);
        if(result.size() <= toInsert) {
          result.resize(toInsert + 1);
        }
        ++result[toInsert];
      }
    }
    return result;
  }
  
  void EmptyStripsTracker::recomputeEmptyStrips(int positionX,
                                                int positionY,
                                                int rectangleWidth,
                                                int rectangleHeight)
  {
    // Compute horizontal strips
    for(int line = positionY; line < positionY + rectangleHeight; ++line) {
      int contiguousEmptySpace = 0;
      for(int column = 0; column < occupationMatrix.width; column++) {
        if(occupationMatrix.query(Point(column, line)) == -1) {
          ++contiguousEmptySpace;
        }
        else {
          for(int i = 1; i <= contiguousEmptySpace; ++i) {
            horizontalEmptyStrips[column - i][line] = contiguousEmptySpace;
          }
          contiguousEmptySpace = 0;
          horizontalEmptyStrips[column][line] = 0;
          // TODO: Jump j of the size of the vector
        }
      }
      for(int i = 1; i <= contiguousEmptySpace; ++i) {
        horizontalEmptyStrips[occupationMatrix.width - i][line] = contiguousEmptySpace;
      }
    }

    // Compute vertical strips
    for(int column = positionX; column < positionX + rectangleWidth; ++column) {
      int contiguousEmptySpace = 0;
      for(int line = 0; line < occupationMatrix.height; line++) {
        if(occupationMatrix.query(Point(column, line)) == -1) {
          ++contiguousEmptySpace;
        }
        else {
          std::fill_n(verticalEmptyStrips[column].begin() + line - contiguousEmptySpace,
                      contiguousEmptySpace,
                      contiguousEmptySpace);
          contiguousEmptySpace = 0;
          verticalEmptyStrips[column][line] = 0;
          // TODO: Jump j of the size of the vector
        }
      }
      std::fill_n(verticalEmptyStrips[column].begin() + occupationMatrix.height - contiguousEmptySpace,
                  contiguousEmptySpace,
                  contiguousEmptySpace);
    }
  }

}
