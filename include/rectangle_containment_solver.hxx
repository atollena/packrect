#ifndef RECTANGLE_CONTAINMNET_SOLVER_HXX
#define RECTANGLE_CONTAINMNET_SOLVER_HXX

#include <vector>

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
                               const BoundingBox& boundingBox);

    /**
     * Solves the containment problem for a given bounding box and a
     * set of rectangles
     *
     * @return a vector with the position of rectangles fitting in the
     *         bounding box, or an empty vector if there is no
     *         solution.
     */
    std::vector<RectanglePosition> compute();
  private:

    /**
     *
     */
    std::vector<RectanglePosition> firstRectangleCandidatePosition();


    const std::vector<Rectangle>& input;
    const BoundingBox boundingBox;

    BoxOccupationMatrix occupationMatrix;
  };
}

#endif // RECTANGLE_CONTAINMNET_SOLVER_HXX
