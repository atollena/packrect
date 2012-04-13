#include <algorithm>

#include "optimal_rectangle_packing.hxx"
#include "rectangle_containment_solver.hxx"
#include "rectangle.hxx"

namespace packing {

  OptimalRectanglePacking::OptimalRectanglePacking(std::vector<Rectangle> input)
    : input()
  {
    std::sort(input.begin(), input.end(), Rectangle::BiggerWidth());
  }

  OptimalRectanglePacking::Packing OptimalRectanglePacking::compute() const
  {
    BoundingBox currentBox (11, 8);

    RectangleContainmentSolver(input, currentBox).compute();

    return std::make_pair(currentBox,
                          std::vector<RectanglePosition>());
  }
}
