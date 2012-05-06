#ifndef BOX_OCCUPATION_MATRIX_HXX
#define BOX_OCCUPATION_MATRIX_HXX

#include <ostream>
#include <vector>
#include <deque>

#include "rectangle.hxx"
#include "rectangle_size.hxx"

namespace packing {

  class RectanglePosition;
  class BoundingBox;
  class Point;

  /**
   * Keeps track of what is currently filled with a rectangle and what
   * is free in the bounding box. Should have decent performance.
   */
  class BoxOccupationMatrix {
  public:
    /**
     * Creates a new matrix of size width * height
     */
    BoxOccupationMatrix(const RectangleSize & boxSize);

    /**
     * Checks if position x, y is occupied
     *
     * @return true if the
     */
    RectangleId query(const Point & position) const;

    /**
     * Set area for given rectangle and position as occupied
     */
    void set(const Rectangle & rectangle,
             const RectanglePosition & position);

    /**
     * Reset area for given rectangle and position as free
     */
    void unset(const Rectangle & rectangle,
               const RectanglePosition & position);



    /**
     * Print out the content of the bounding box in a user-friendly
     * fashion (for debugging, use solutionToString for pretty
     * printing)
     */
    friend std::ostream& operator<<(std::ostream& out, const BoxOccupationMatrix& box);

  private:
    int width;
    int height;
    std::vector<RectangleId> matrix;

    /**
     * Sets occupation at position with width and height to the given
     * rectangle id.
     */
    void set(const Point & position,
             int width,
             int height,
             RectangleId id);

    /**
     * Return an iterator pointing to coording x, y
     */
    std::vector<RectangleId>::iterator at(int x, int y);

    /**
     * Returns the element with coordonate x, y
     */
    RectangleId at(int x, int y) const;


    // TODO: Document and refactor
  public:
    std::deque<int> minContiguousFreeCells() const;

  private:
    std::vector<std::vector<int>> verticalEmptyStrips;
    std::vector<std::vector<int>> horizontalEmptyStrips;

    void recomputeEmptyStrips(int positionX,
                              int positionY,
                              int rectangleWidth,
                              int rectangleHeight);
  };
}



#endif // BOX_OCCUPATION_MATRIX_HXX
