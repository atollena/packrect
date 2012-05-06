#ifndef RECTANGLE_SIZE_HXX
#define RECTANGLE_SIZE_HXX

#include <functional>

namespace packing {
  struct RectangleSize {
    RectangleSize(int width, int height)
      :width(width), height(height)
    {}
  
    int computeArea() const
    {
      return width * height;
    }

    int width;
    int height;

    /**
     * Compare rectangles sizes based on their area
     */
    struct SmallerArea : public std::binary_function<RectangleSize, RectangleSize, bool>
    {
      bool operator()(const RectangleSize & first,
                      const RectangleSize & second) const
      {
        return first.computeArea() < second.computeArea();
      };
    };
  };
}

#endif // RECTANGLE_SIZE_HXX
