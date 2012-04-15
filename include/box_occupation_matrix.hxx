#ifndef BOX_OCCUPATION_MATRIX_HXX
#define BOX_OCCUPATION_MATRIX_HXX

#include <ostream>
#include <vector>

namespace packing {

  class RectanglePosition;
  class Rectangle;
  class BoundingBox;
  class Point;

  /**
   * Rectangle identifier
   */
  typedef int RectangleId;

  /**
   * Keeps track of what is currently filled with a rectangle and what
   * is free in the bounding box. Should have decent performance.
   */
  class BoxOccupationMatrix {
  public:
    /**
     * Creates a new matrix of size width * height
     */
    BoxOccupationMatrix(BoundingBox boundingBox);

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
             const RectanglePosition & position,
             const RectangleId & );

    /**
     * Reset area for given rectangle and position as free
     */
    void unset(const Rectangle & rectangle,
               const RectanglePosition & position);

    /**
     * Print out the content of the matrix in a user-friendly fashion
     */
    friend std::ostream& operator<<(std::ostream& out, const BoxOccupationMatrix& box);

  private:
    std::vector<RectangleId> matrix;
    const int width;
    const int height;

    /**
     * Return an iterator pointing to coording x, y
     */
    std::vector<RectangleId>::iterator at(int x, int y);

    /**
     * Returns the element with coordonate x, y
     */
    RectangleId at(int x, int y) const;
  };
}



#endif // BOX_OCCUPATION_MATRIX_HXX
