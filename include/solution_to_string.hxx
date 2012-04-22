#ifndef SOLUTION_TO_STRING_HXX
#define SOLUTION_TO_STRING_HXX

#include <string>
#include <vector>
#include <list>

#include "point.hxx"

namespace packing {

  class BoundingBox;
  class Rectangle;
  class RectanglePosition;

  std::string solutionToString (const BoundingBox & box,
                                const std::vector<Rectangle> & rectangles,
                                const std::list<RectanglePosition> & position);
}

#endif // SOLUTION_TO_STRING_HXX
