#ifndef SOLUTION_TO_STRING_HXX
#define SOLUTION_TO_STRING_HXX

#include <string>
#include <vector>
#include <list>

#include "point.hxx"
#include "rectangle_size.hxx"

namespace packing {

  class Rectangle;
  class RectanglePosition;

  std::string solutionToString (const RectangleSize & box,
                                const std::vector<Rectangle> & rectangles,
                                const std::list<RectanglePosition> & position);
}

#endif // SOLUTION_TO_STRING_HXX
