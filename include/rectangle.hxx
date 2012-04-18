#ifndef RECTANGLE_HXX
#define RECTANGLE_HXX

#include <functional>

namespace packing {
  typedef int RectangleId;

  /**
   * Class for representing a rectangle. To make certain operations
   * more efficient, we impose width >= height.
   */
  class Rectangle {
  public:
    Rectangle (int width, int height, RectangleId id);
    Rectangle(const Rectangle & other);
    Rectangle& operator= (const Rectangle & other);
    bool operator== (const Rectangle & other) const;

    ~Rectangle();
    
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
  private:
    RectangleId id;
    int width;
    int height;
  };
}

#endif // RECTANGLE_HXX
