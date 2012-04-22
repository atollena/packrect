#ifndef RECTANGLE_HXX
#define RECTANGLE_HXX

#include <vector>
#include <functional>

#include "point.hxx"

namespace packing {
  class Point;
  class RectanglePosition;

  typedef int RectangleId;

  /**
   * Class for representing a rectangle. To make certain operations
   * more efficient, we impose width >= height.
   */
  class Rectangle {
  public:
    Rectangle (int width, int height, RectangleId id);
    bool operator== (const Rectangle & other) const;

    int getH() const;
    int getW() const;
    RectangleId getId() const;
    bool isSquare () const;

    /**
     * Compare rectangles based on the size of their width. Used to
     * sort rectangle in the order we are going to place them
     * (increasing longest width)
     */
    struct BiggerWidth : public std::binary_function<Rectangle, Rectangle, bool>
    {
      bool operator()(const Rectangle & first, const Rectangle & second) const;
    };

    /**
     * Compare rectangles based on the size of their height
     */
    struct BiggerHeight : public std::binary_function<Rectangle, Rectangle, bool>
    {
      bool operator()(const Rectangle & first, const Rectangle & second) const;
    };
  private:
    RectangleId id;
    int width;
    int height;
  };
}

#endif // RECTANGLE_HXX
