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
     verticalEmptyStrips(width, std::vector<int>(height, height)),
     horizontalEmptyStrips(width, std::vector<int>(height, width))
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

    recomputeEmptyStrips(position.getX(),
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

  void BoxOccupationMatrix::recomputeEmptyStrips(int positionX,
                                                 int positionY,
                                                 int rectangleWidth,
                                                 int rectangleHeight)
  {
    // Compute horizontal strips
    for(int line = positionY; line < positionY + rectangleHeight; ++line) {
      int contiguousEmptySpace = 0;
      for(int column = 0; column < width; column++) {
        if(query(Point(column, line)) == -1) {
          ++contiguousEmptySpace;
        }
        else {
          for(int i = 0; i < contiguousEmptySpace; ++i) {
            horizontalEmptyStrips[column - i][line] = contiguousEmptySpace;
          }
          contiguousEmptySpace = 0;
          verticalEmptyStrips[column][line] = 0;
          // TODO: Jump j of the size of the vector
        }
      }
      for(int i = 1; i <= contiguousEmptySpace; ++i) {
        horizontalEmptyStrips[width - i][line] = contiguousEmptySpace;
      }
    }

    // Compute vertical strips
    for(int column = positionX; column < positionX + rectangleWidth; ++column) {
      int contiguousEmptySpace = 0;
      for(int line = 0; line < height; line++) {
        if(query(Point(column, line)) == -1) {
          ++contiguousEmptySpace;
        }
        else {
          std::fill_n(verticalEmptyStrips[column].begin() + line - contiguousEmptySpace,
                      contiguousEmptySpace,
                      contiguousEmptySpace);
          contiguousEmptySpace = 0;
          verticalEmptyStrips[column][line] = 0;
          // TODO: Jump j of the size of the vector
        }
      }
      std::fill_n(verticalEmptyStrips[column].begin() + height - contiguousEmptySpace,
                  contiguousEmptySpace,
                  contiguousEmptySpace);
    }
  }

  std::deque<int>
  BoxOccupationMatrix::minContiguousFreeCells() const
  {
    std::deque<int> result;
    for(unsigned int i = 0; i < verticalEmptyStrips.size(); ++i) {
      for(unsigned int j = 0; j < verticalEmptyStrips[i].size(); ++j) {
        unsigned int toInsert = std::min(verticalEmptyStrips[i][j],
                                         horizontalEmptyStrips[i][j]);
        if(result.size() <= toInsert) {
          result.resize(toInsert + 1);
        }
        ++result[toInsert];
      }
    }
    return result;
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
