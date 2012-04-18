#include "bounding_box.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"

namespace packing {
  BoundingBox::BoundingBox(int width, int height)
    :width(width), height(height), occupationMatrix(*this) {}

  int BoundingBox::area() const
  {
    return width*height;
  }

  int BoundingBox::getHeight() const { return height; }
  int BoundingBox::getWidth() const { return width; }

  void BoundingBox::set(const Rectangle & rectangle,
                        const RectanglePosition & position)
  {
    occupationMatrix.set(rectangle, position);
  }

  void BoundingBox::unset(const Rectangle & rectangle,
                          const RectanglePosition & position)
  {
    occupationMatrix.unset(rectangle, position);
  }

  std::vector<RectanglePosition>
  BoundingBox::firstRectangleCandidatePosition(const Rectangle & rectangle) const
  {    
    // To exploit the symmetry of the problem: we place the first
    // rectangle in the bottom left part of the bounding box.
    int xMax = (getWidth() - 1) / 2 + 1;
    int yMax = (getHeight() - 1) / 2 + 1;

    std::vector<RectanglePosition> result;
    result.reserve(xMax * yMax);

    for(int i = 0; i < yMax; ++i) {
      for(int j = 0; j < xMax; ++j) {
        const RectanglePosition hPosition = RectanglePosition(Point(j, i), false);
        if(isValid(hPosition, rectangle)) {
          result.push_back(hPosition);
        }

        if(!rectangle.isSquare()) {
          const RectanglePosition vPosition = RectanglePosition(Point(j, i), true);
          if(isValid(vPosition, rectangle)) {
            result.push_back(RectanglePosition(Point(j, i), true));
          }
        }
      }
    }

    return result;
  }

  std::deque<RectanglePosition>
  BoundingBox::candidatePosition(const Rectangle & rectangle) const {
    std::deque<RectanglePosition> result;
    for(int i = 0; i < getHeight(); i++) {
      for(int j = 0; j < getWidth(); j++) {
        // Iterate on the width first as it maximizes cache locality
        // due to the way the bouding box matrix is stored
        checkAndInsertPosition(j, i, rectangle, result);
      }
    }
    return result;
  }

  bool BoundingBox::isValid(const RectanglePosition & position,
                            const Rectangle & rectangle) const
  {
    int rectangleWidth = rectangle.getW();
    int rectangleHeight = rectangle.getH();
    if(position.isVertical()) {
      std::swap(rectangleWidth, rectangleHeight);
    }
    
    // Checks if bounds of rectangle are in the box
    if(position.getLeftBottomX() + rectangleWidth > width ||
       position.getLeftBottomY() + rectangleHeight > height) {
      return false;
    }

    // Checks if bounds of rectangle are occupied
    for(int i = position.getLeftBottomY(); i < position.getLeftBottomY() + rectangleHeight; ++i) {
      for (int j = position.getLeftBottomX(); j < position.getLeftBottomX() + rectangleWidth; ++j) {
        if(occupationMatrix.query(Point(j, i)) != -1) {
          return false;
        }
      }
    }
    // As we place rectangles in decreasing order of size, current
    // rectangle can't possibly be a contained in another.
    return true;
  }

  std::vector<RectanglePosition> BoundingBox::getSolution() const
  {
    return std::vector<RectanglePosition>(); // TODO
  }

  void BoundingBox::checkAndInsertPosition(int i, int j,
                                           const Rectangle & rectangle,
                                           std::deque<RectanglePosition> & result) const
  {
    const RectanglePosition hPosition = RectanglePosition(Point(i, j), false);
    if(isValid(hPosition, rectangle)) {
      result.push_back(hPosition);
    }

    if(! rectangle.isSquare()) {
      const RectanglePosition vPosition = RectanglePosition(Point(i, j), true);
      if(isValid(vPosition, rectangle)) {
        result.push_back(vPosition);
      }
    }
  }
}
