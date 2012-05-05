#ifndef CONSTANT_HXX
#define CONSTANT_HXX

#include <vector>

#include "rectangle.hxx"

namespace packing {
  /**
   * Defines invariants for the problem, that can be passed around in
   * our solution, for instance for precomputed result
   */
  struct Invariants {
    Invariants(const std::vector<Rectangle> & input);
    
    const std::vector<Rectangle> input;
    int totalRectangleArea;
  };
}

#endif
