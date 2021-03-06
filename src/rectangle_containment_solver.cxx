#include <deque>
#include <list>
#include <cassert>

#include "rectangle_containment_solver.hxx"
#include "rectangle.hxx"

namespace packing {

  RectangleContainmentSolver::RectangleContainmentSolver(const Invariants & invariants,
                                                         const RectangleSize & size)
    :invariants(invariants),
     boundingBox(size)
#ifdef STATISTICS
    , backtrackNodes(0)
#endif
  {
    assert(!invariants.input.empty());
    assert(size.width != 0 &&
           size.height != 0);
  }

  std::list<RectanglePosition> RectangleContainmentSolver::compute()
  {
    auto input = invariants.input;
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

#ifdef STATISTICS
    ++backtrackNodes;
#endif
    
    std::deque<RectanglePosition> candidatePositions =
      boundingBox.candidatePosition(*first);
    
    for(RectanglePosition position : candidatePositions) {
      boundingBox.set(*first, position);
      if(! boundingBox.isPruned(first + 1, last,
                                invariants.totalRectangleArea) &&
         backtrack(first + 1, last))
        return true;
      boundingBox.unset(*first);
    }
    return false;
  }
}

