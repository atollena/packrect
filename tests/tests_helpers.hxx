#ifndef TESTS_HELPER_HXX
#define TESTS_HELPER_HXX

#include <vector>

namespace packing {
  class Rectangle;

  /**
   * Creates rectangles with height == width and dimensions
   * from n to 1
   */
  std::vector<Rectangle> createDecrementingSquares(int n);

  /**
   * Creates a vector of rectangle having width == (height + 1), with
   * size from n to 1
   */
  std::vector<Rectangle> createDecrementingRectangles(int n);
}
#endif
