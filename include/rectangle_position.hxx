#ifndef RECTANGLE_POSITION_HXX
#define RECTANGLE_POSITION_HXX

#include "point.hxx"

namespace packing {
  /**
   * Stores the position of a rectangle in the bounding box
   */
  class RectanglePosition {
  public:
    RectanglePosition(Point leftBottom, bool vertical);
    bool operator==(const RectanglePosition& other) const;
    Point getLeftBottom() const;
    int getLeftBottomX() const;
    int getLeftBottomY() const;
    bool isVertical() const;
  private:
    Point leftBottom;
    bool vertical;
  };
}

#endif // RECTANGLE_POSITION_HXX


