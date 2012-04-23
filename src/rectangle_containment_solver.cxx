#include <deque>
#include <list>

#include "rectangle_containment_solver.hxx"
#include "rectangle_position.hxx"
#include "rectangle.hxx"

namespace packing {

  RectangleContainmentSolver::RectangleContainmentSolver(const std::vector<Rectangle>& input,
                                                         const RectangleSize & size)
    :input(input), boundingBox(size)
  {}

  std::list<RectanglePosition> RectangleContainmentSolver::compute()
  {
    if (input.empty())
      return std::list<RectanglePosition>();
    
    for(RectanglePosition iter:
          boundingBox.firstRectangleCandidatePosition(input.front())) {
      boundingBox.set(input.front(), iter);
      if(backtrack(input.begin() + 1, input.end()))
        break;
      boundingBox.unset(input.front());
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
      if(backtrack(first + 1, last))
        return true;
      boundingBox.unset(*first);
    }
    return false;
  }
}

