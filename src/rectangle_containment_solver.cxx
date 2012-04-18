#include <deque>

#include "rectangle_containment_solver.hxx"
#include "rectangle_position.hxx"
#include "rectangle.hxx"

namespace packing {

  RectangleContainmentSolver::RectangleContainmentSolver(const std::vector<Rectangle>& input,
                                                         const BoundingBox& boundingBox)
    :input(input), boundingBox(boundingBox)
  {}

  std::vector<RectanglePosition> RectangleContainmentSolver::compute()
  {
    if (input.empty())
      return std::vector<RectanglePosition>();
    
    for(RectanglePosition iter:
          boundingBox.firstRectangleCandidatePosition(input.front())) {
      boundingBox.set(input.front(), iter);
      if(backtrack(++input.begin(), input.end()))
        break;
      boundingBox.unset(input.front(), iter);
    }

    return boundingBox.getSolution();
  }

  bool
  RectangleContainmentSolver::backtrack(std::vector<Rectangle>::const_iterator first,
                                        std::vector<Rectangle>::const_iterator last)
  {
    if(first == last)
      return true;
    
    std::deque<RectanglePosition> candidatePositions =
      boundingBox.candidatePosition(*first);
    
    for(RectanglePosition position : candidatePositions) {
      boundingBox.set(*first, position);
      if(backtrack(++first, last))
        return true;
      boundingBox.unset(*first, position);
    }
    return false;
  }
}

