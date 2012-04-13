#ifndef RECTANGLE_POSITION_HXX
#define RECTANGLE_POSITION_HXX

namespace packing {
  /**
   * Stores the position of a rectangle in the bounding box
   */
  class RectanglePosition {
  public:
    RectanglePosition(int x, int y);
    bool operator==(const RectanglePosition& other) const;
    int getX() const;
    int getY() const;
  private:
    int x;
    int y;
  };
}

#endif // RECTANGLE_POSITION_HXX


