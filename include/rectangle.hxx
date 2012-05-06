#ifndef RECTANGLE_HXX
#define RECTANGLE_HXX

#include <cassert>
#include <functional>
#include <vector>

#include "point.hxx"
#include "rectangle_position.hxx"

namespace packing {
  class Point;

  typedef int RectangleId;

  /**
   * Class for representing a rectangle. To make certain operations
   * more efficient, we impose width >= height.
   */
  class Rectangle {
  public:
    Rectangle (int width, int height, RectangleId id)
      : id(id), width(width), height(height)
    {
      // Check that we meet the class requirements
      assert(width >= height);
    };
    
    bool operator== (const Rectangle & other) const
    {
      return other.width == width && other.height == height;
    }

    int getH() const { return height; }
    int getW() const { return width; }
    RectangleId getId() const { return id; };
    bool isSquare () const { return height == width; };
    int getArea() const { return width * height; };

    /**
     * Compare rectangles based on the size of their width. Used to
     * sort rectangle in the order we are going to place them
     * (increasing longest width)
     */
    struct BiggerWidth : public std::binary_function<Rectangle, Rectangle, bool>
    {
      bool operator()(const Rectangle & first, const Rectangle & second) const
        {
          return first.getW() > second.getW();
        }
    };

    /**
     * Compare rectangles based on the size of their height
     */
    struct BiggerHeight : public std::binary_function<Rectangle, Rectangle, bool>
    {
      bool operator()(const Rectangle & first, const Rectangle & second) const
      {
        return first.getH() > second.getH();
      }
    };
  private:
    RectangleId id;
    int width;
    int height;
  };
}

#endif // RECTANGLE_HXX
