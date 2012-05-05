#ifndef BOUNDING_BOX_HXX
#define BOUNDING_BOX_HXX

#include <list>
#include <deque>

#include "box_occupation_matrix.hxx"
#include "rectangle_size.hxx"

namespace packing {
  class Rectangle;
  class RectanglePosition;

  /**
   * Stores temporary rectangle placements.
   */
  class BoundingBox {
  public:
    BoundingBox(const RectangleSize & size);
    
    /**
     * Computes the area of the bounding box
     */
    int computeArea() const;

    /**
     * Checks if we should try this position according to our pruning
     * strategy
     */
    bool isPruned(std::vector<Rectangle>::const_iterator first,
                  std::vector<Rectangle>::const_iterator last,
                  int totalRectanglesArea) const;

    /**
     * Set the rectangle to the given position
     */
    void set(const Rectangle & rectangle,
             const RectanglePosition & position);

    /**
     * Unset the last stored position
     */
    void unset(const Rectangle & rectangle);

    /**
     * Returns a list of valid positions to place the given
     * rectangle if it is the first rectangle to place
     */
    std::vector<RectanglePosition>
    firstRectangleCandidatePosition(const Rectangle & rectangle) const;

    /**
     * Returns the list of valid positions for the given rectangle,
     * taking already placed rectangles in consideration
     */
    std::deque<RectanglePosition>
    candidatePosition(const Rectangle & rectangle) const;

    /**
     * Returns the list of rectangle position currently in the box
     */
    std::list<RectanglePosition> getSolution() const;

  private:
    const RectangleSize size;
    
    BoxOccupationMatrix occupationMatrix;
    std::list<RectanglePosition> currentSolution;

    /**
     * Checks if position of rectangle is in the bounding box and does
     * not overlap with any other rectangle
     */
    bool isValid(const Rectangle & rectangle,
                 const RectanglePosition & position) const;

    /**
     * Checks if a rectangle at this position is contained in the
     * bounding box
     */
    bool isInBox(const Rectangle & rectangle,
                 const RectanglePosition & position) const;

    /**
     * Checks if rectangle at this position overlaps with already
     * placed rectangles
     */
    bool hasNoOverlap(const Rectangle & rectangle,
                      const RectanglePosition & position) const;

    /**
     * Insert positions (i, j), both horizontal and vertical, of
     * rectangle in result if they fit in the bounding box
     */
    void checkAndInsertPosition(int i, int j,
                                const Rectangle & rectangle,
                                std::deque<RectanglePosition> & result) const;
  };
}

#endif // BOUNDING_BOX_HXX
