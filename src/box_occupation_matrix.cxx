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
     matrix(boxSize.computeArea(), -1)
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

    for(int i = 0; i < rectangleHeight; ++i) {
      std::fill_n(at(position.getLeftBottomX(), position.getLeftBottomY() + i),
                  rectangleWidth,
                  rectangle.getId());
    }
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

  void BoxOccupationMatrix::set(Point position,
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
  }

  std::vector<RectangleId>::iterator BoxOccupationMatrix::at(int x, int y)
  {
    return matrix.begin() + (y*width + x);
  }

  RectangleId BoxOccupationMatrix::at(int x, int y) const
  {
    return matrix[y*width + x];
  }

  int BoxOccupationMatrix::minContiguousFreeCells(const Point & position) const
  {
    if(query(position) != -1)
      return 0;
    
    int freeOnTheLeft = position.getX();
    while(freeOnTheLeft >= 0 && query(Point(freeOnTheLeft, position.getY())) == -1) {
      --freeOnTheLeft;
    }
    ++freeOnTheLeft;
    
    int freeOnTheRight = position.getX();
    while(freeOnTheRight < width && query(Point(freeOnTheRight,
                                                position.getY())) == -1) {
      ++freeOnTheRight;
    }
    --freeOnTheRight;

    int freeOnBottom = position.getY();
    while(freeOnBottom >= 0 && query(Point(position.getX(),
                                              freeOnBottom)) == -1) {
      --freeOnBottom;
    }
    ++freeOnBottom;
    
    int freeOnTop = position.getY();
    while(freeOnTop < height && query(Point(position.getX(),
                                            freeOnTop)) == -1) {
      ++freeOnTop;
    }
    --freeOnTop;

    int horizontalContiguousFreeCells = freeOnTheRight - freeOnTheLeft + 1;
    int verticalContiguousFreeCells = freeOnTop - freeOnBottom + 1;

    return std::min(verticalContiguousFreeCells,
                    horizontalContiguousFreeCells);
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
          out << 'x';
      }
      out << std::endl;
    }
    return out;
  }
}
