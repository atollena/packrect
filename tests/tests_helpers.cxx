#include "tests_helpers.hxx"
#include "rectangle.hxx"

namespace packing {
  std::vector<Rectangle> createDecrementingSquares(int n)
  {
    std::vector<Rectangle> input;
    for(int i = n; i >= 1; i--) {
      input.push_back(Rectangle(i, i, i));
    }
    return input;
  }

  std::vector<Rectangle> createDecrementingRectangles(int n)
  {
    std::vector<Rectangle> input;
    for(int i = n; i >= 1; i--) {
      input.push_back(Rectangle(i, i, i));
    }
    return input;
  }

  std::vector<Rectangle> createSameRectangles(int n)
  {
    std::vector<Rectangle> input;
    input.reserve(n);
    for(int i = n; i >= 1; i--) {
      input.push_back(Rectangle(2, 1, i));
    }
    return input;
  }
}
