#include <algorithm>

#include "box_occupation_matrix.hxx"

#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "bounding_box.hxx"

namespace packing {

  BoxOccupationMatrix::BoxOccupationMatrix(BoundingBox boundingBox)
    :matrix(boundingBox.getWidth()*boundingBox.getHeight(), -1),
     width(boundingBox.getWidth()),
     height(boundingBox.getHeight())
  {

  }

  RectangleId BoxOccupationMatrix::query(const Point & position) const
  {
    return at(position.getX(), position.getY());
  }

  void BoxOccupationMatrix::set(const Rectangle & rectangle,
                                const RectanglePosition & position,
                                const RectangleId& rectangleNumber)
  {
    int height = rectangle.getH();
    int width = rectangle.getW();
    if(position.isVertical()) {
      std::swap(height, width);
    }

    for(int i = 0; i < height; ++i) {
      std::fill_n(at(position.getLeftBottomX(), position.getLeftBottomY() + i),
                  width,
                  rectangleNumber);
    }
  }

  void BoxOccupationMatrix::unset(const Rectangle & rectangle,
                                  const RectanglePosition & position)
  {
    set(rectangle, position, -1);
  }

  std::vector<RectangleId>::iterator BoxOccupationMatrix::at(int x, int y)
  {
    return matrix.begin() + (y*width + x);
  }

  RectangleId BoxOccupationMatrix::at(int x, int y) const
  {
    return matrix[y*width + x];
  }

  static int maxDigit(std::vector<int> vec)
  {
    int maxDigits = *std::max_element(vec.begin(), vec.end());
    int digits = 0;
    if(maxDigits > 0) {
      while (maxDigits != 0) {
        maxDigits /= 10; digits++;
      }
    }
    return digits;
  }

  std::ostream& operator<<(std::ostream& out, const BoxOccupationMatrix& box)
  {
    int maxDigits = maxDigit(box.matrix);
    out << std::endl;
    for(int y = box.height - 1; y >= 0; y--) {
      for(int x = 0; x < box.width; x++) {
        out.width(maxDigits + 1);
        if(box.at(x, y) != -1)
          out << box.at(x, y);
        else
          out << ' ';
      }
      out << std::endl;
    }
    return out;
  }
}
