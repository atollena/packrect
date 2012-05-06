#include <algorithm>
#include <cassert>

#include "box_occupation_matrix.hxx"

#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "bounding_box.hxx"

namespace packing {

  BoxOccupationMatrix::BoxOccupationMatrix(const RectangleSize & boxSize)
    :width(boxSize.width),
     height(boxSize.height),
     matrix(boxSize.computeArea(), -1),
     emptyStripsTracker(*this)
  {}

  RectangleId BoxOccupationMatrix::query(const Point & position) const
  {
    assert(position.getX() >= 0);
    assert(position.getY() >= 0);
    assert(position.getX() < width);
    assert(position.getY() < height);

    return at(position.getX(), position.getY());
  }

  void BoxOccupationMatrix::set(const Rectangle & rectangle,
                                const RectanglePosition & position)
  {
    int rectangleHeight = rectangle.getH();
    int rectangleWidth = rectangle.getW();
    if(position.isVertical()) {
      std::swap(rectangleHeight, rectangleWidth);
    }

    set(position.getLeftBottom(),
        rectangleWidth,
        rectangleHeight,
        rectangle.getId());
  }

  void BoxOccupationMatrix::unset(const Rectangle & rectangle,
                                  const RectanglePosition & position)
  {
    int rectangleHeight = rectangle.getH();
    int rectangleWidth = rectangle.getW();
    if(position.isVertical()) {
      std::swap(rectangleHeight, rectangleWidth);
    }
    set(position.getLeftBottom(),
        rectangleWidth,
        rectangleHeight,
        -1);
  }

  void BoxOccupationMatrix::set(const Point & position,
                                int rectangleWidth,
                                int rectangleHeight,
                                RectangleId id)
  {
    assert(position.getX() + rectangleWidth <= this->width);
    assert(position.getY() + rectangleHeight <= this->height);

    for(int i = 0; i < rectangleHeight; ++i) {
      std::fill_n(at(position.getX(), position.getY() + i),
                  rectangleWidth,
                  id);
    }

    emptyStripsTracker.recomputeEmptyStrips(position.getX(),
                                            position.getY(),
                                            rectangleWidth,
                                            rectangleHeight);
  }

  std::vector<RectangleId>::iterator BoxOccupationMatrix::at(int x, int y)
  {
    return matrix.begin() + (y*width + x);
  }

  RectangleId BoxOccupationMatrix::at(int x, int y) const
  {
    return matrix[y*width + x];
  }

  std::deque<int>
  BoxOccupationMatrix::minContiguousFreeCells() const
  {
    return emptyStripsTracker.minContiguousFreeCells();
  }

  namespace {
    int maxDigit(std::vector<int> vec)
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
          out << 'x';
      }
      out << std::endl;
    }
    return out;
  }
}
