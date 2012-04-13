#include "rectangle_containment_solver.hxx"
#include "rectangle_position.hxx"
#include "rectangle.hxx"

namespace packing {

  RectangleContainmentSolver::RectangleContainmentSolver(const std::vector<Rectangle>& input,
                                                         const BoundingBox& boundingBox)
    :input(input), boundingBox(boundingBox)
  {}

  std::vector<RectanglePosition> RectangleContainmentSolver::compute() const
  {
    return std::vector<RectanglePosition>();
  }
}
