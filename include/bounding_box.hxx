#ifndef BOUNDING_BOX_HXX
#define BOUNDING_BOX_HXX

#include <deque>
#include <memory>

#include "box_occupation_matrix.hxx"
namespace packing {
  class Rectangle;
  class RectanglePosition;

  /**
   * High level functions for querying the bouding box
   */
  class BoundingBox {
  public:
    BoundingBox(int width, int height);
    int getHeight() const;
    int getWidth() const;
    int area() const;

    void set(const Rectangle & rectangle,
             const RectanglePosition & position);

    void unset(const Rectangle & rectangle,
               const RectanglePosition & position);
    
    std::vector<RectanglePosition>
    firstRectangleCandidatePosition(const Rectangle & rectangle) const;
    
    std::deque<RectanglePosition>
    candidatePosition(const Rectangle & rectangle) const;

    std::vector<RectanglePosition> getSolution() const;

    /**
     * Print out the content of the bounding box in a user-friendly
     * fashion
     */
    friend std::ostream& operator<<(std::ostream& out, const BoundingBox& box);
    
  private:
    const int width;
    const int height;
    BoxOccupationMatrix occupationMatrix;
    std::shared_ptr<std::vector<Rectangle>> input;

    /**
     * Checks if position of rectangle is in the bounding box and does
     * not overlap with any other rectangle
     */
    bool isValid(const RectanglePosition & position,
                 const Rectangle & rectangle) const;

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
