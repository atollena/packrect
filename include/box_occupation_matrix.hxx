#ifndef BOX_OCCUPATION_MATRIX_HXX
#define BOX_OCCUPATION_MATRIX_HXX

#include <ostream>
#include <vector>

namespace packing {

  class RectanglePosition;
  class Rectangle;

  /**
   * Keeps track of what is currently filled with a rectangle and what
   * is free in the bounding box. Should have decent performance.
   */
  class BoxOccupationMatrix {
  public:
    enum Content {
      FREE,
      OCCUPIED
    };
    
    /**
     * Creates a new matrix of size width * height
     */
    BoxOccupationMatrix(int width, int height);

    /**
     * Checks if position x, y is occupied
     *
     * @return true if the 
     */
    Content query(const RectanglePosition & position) const;

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
     * Reset the entire matrix to unoccupied
     */
    void reset();

    friend std::ostream& operator<<(std::ostream& out, const BoxOccupationMatrix& box);

  private:
    std::vector<Content> matrix;
    const int width;
    const int height;

    void set(const Rectangle & rectangle,
             const RectanglePosition & position,
             Content content);
    std::vector<Content>::iterator at(int x, int y);
    Content at(int x, int y) const;
  };
}



#endif // BOX_OCCUPATION_MATRIX_HXX
