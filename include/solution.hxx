#ifndef SOLUTION_HXX
#define SOLUTION_HXX

#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "rectangle_size.hxx"

namespace packing {
  struct Solution {
    Solution(const RectangleSize & boxSize,
             const std::vector<Rectangle> & rectangles,
             const std::list<RectanglePosition> & rectanglePositions)
      :boxSize(boxSize),
       rectangles(rectangles),
       rectanglePositions(rectanglePositions)
    {}

    const RectangleSize boxSize;
    const std::vector<Rectangle> rectangles;
    const std::list<RectanglePosition> rectanglePositions;
  };
}

#endif
