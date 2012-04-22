#ifndef RECTANGLE_POSITION_HXX
#define RECTANGLE_POSITION_HXX

#include "point.hxx"

#include <vector>

namespace packing {

  class Rectangle;

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

    std::vector<Point> getTopLine(const Rectangle & rectangle) const;
    std::vector<Point> getBottomLine(const Rectangle & rectangle) const;
    std::vector<Point> getLeftLine(const Rectangle & rectangle) const;
    std::vector<Point> getRightLine(const Rectangle & rectangle) const;

    Point getTopRight(const Rectangle & rectangle) const;
    Point getTopLeft(const Rectangle & rectangle) const;
    Point getBottomRight(const Rectangle & rectangle) const;

    std::vector<Point> getSides(const Rectangle & rectangle) const;

    bool isVertical() const;
  private:
    enum class LineType { LEFT, RIGHT, BOTTOM, TOP};

    std::vector<Point> getLine(const Rectangle & rectangle,
                               const LineType & lineType) const;

    int getHorizontalSize(const Rectangle & rectangle) const;
    int getVerticalSize(const Rectangle & rectangle) const;

    Point leftBottom;
    bool vertical;
  };
}

#endif // RECTANGLE_POSITION_HXX


