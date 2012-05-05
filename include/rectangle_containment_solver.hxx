#ifndef RECTANGLE_CONTAINMNET_SOLVER_HXX
#define RECTANGLE_CONTAINMNET_SOLVER_HXX

#include <vector>
#include <list>
#include <stack>

#include "bounding_box.hxx"
#include "rectangle_position.hxx"
#include "box_occupation_matrix.hxx"

namespace packing {
  class Rectangle;

  /**
   * Solver for the rectangle containment problem.
   *
   * The order rectangles are passed in the constructor is the order
   * of the RectanglePosition in the output. For maximum performance,
   * input rectangles should be passed sorted in decreasing order of
   * their biggest dimension, as this will influence how good the
   * constraint solving algorithm performs.
   */
  class RectangleContainmentSolver {
  public:
    RectangleContainmentSolver(const std::vector<Rectangle>& input,
                               const RectangleSize & size);

    /**
     * Solves the containment problem for a given bounding box and a
     * set of rectangles
     *
     * @return a list with the position of rectangles fitting in the
     *         bounding box, or an empty vector if there is no
     *         solution.
     */
    std::list<RectanglePosition> compute();

  private:

    /**
     * Creates a list of possible position for the first rectangle
     * (exploits the problem symmetry, so positions are only in the
     * left bottom 1/4 of the bounding box, as positioning the first
     * rectangle in one of the 3 other quarters would lead to
     * symmetrical solutions).
     *
     * @return List of postitions for the first rectangle
     */
    std::vector<RectanglePosition> firstRectangleCandidatePosition();

    bool backtrack(std::vector<Rectangle>::const_iterator first,

                   std::vector<Rectangle>::const_iterator last);

    std::deque<RectanglePosition>
    candidatePosition(const Rectangle & rectangle) const;
    bool isValid(const RectanglePosition & position,
                 const Rectangle & rectangle) const;

    const std::vector<Rectangle>& input;
    BoundingBox boundingBox;

#ifdef STATISTICS
  public:
    int backtrackNodes; // number of backtracking nodes tried
#endif
  };
}

#endif // RECTANGLE_CONTAINMNET_SOLVER_HXX
