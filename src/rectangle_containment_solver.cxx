#include "rectangle_containment_solver.hxx"
#include "rectangle_position.hxx"
#include "rectangle.hxx"

namespace packing {

  RectangleContainmentSolver::RectangleContainmentSolver(const std::vector<Rectangle>& input,
                                                         const BoundingBox& boundingBox)
    :input(input), boundingBox(boundingBox), occupationMatrix(boundingBox)
  {}

  std::vector<RectanglePosition> RectangleContainmentSolver::compute()
  {
    for(RectanglePosition iter: firstRectangleCandidatePosition()) {
      occupationMatrix.set(input.front(), iter, 0);
      // backtrack();
      occupationMatrix.unset(input.front(), iter);
    }

    return std::vector<RectanglePosition>();
  }

  std::vector<RectanglePosition>
  RectangleContainmentSolver::firstRectangleCandidatePosition()
  {
    // To exploit the symmetry of the problem: we place the first
    // rectangle in the bottom left part of the bounding box.
    int xMax = boundingBox.getWidth() / 2;
    int yMax = boundingBox.getHeight() / 2;

    std::vector<RectanglePosition> result;
    result.reserve(xMax * yMax);

    for(int i = 0; i < xMax; ++i) {
      for(int j = 0; j < yMax; j++) {
        result.push_back(RectanglePosition(Point(i, j), false));
        result.push_back(RectanglePosition(Point(i, j), true));
      }
    }

    return result;
  }
}
