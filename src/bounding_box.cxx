#include <algorithm>

#include "bounding_box.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"

namespace packing {
  BoundingBox::BoundingBox(int width, int height)
    :width(width), height(height), occupationMatrix(*this) {}

  int BoundingBox::getArea() const
  {
    return width*height;
  }

  int BoundingBox::getHeight() const {
    return height;
  }

  int BoundingBox::getWidth() const {
    return width;
  }

  void BoundingBox::set(const Rectangle & rectangle,
                        const RectanglePosition & position)
  {
    currentSolution.push_back(position);
    occupationMatrix.set(rectangle, position);
  }

  void BoundingBox::unset(const Rectangle & rectangle)
  {
    RectanglePosition top = currentSolution.back();
    occupationMatrix.unset(rectangle, top);
    currentSolution.pop_back();
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
        if(isValid(rectangle, hPosition)) {
          result.push_back(hPosition);
        }

        if(!rectangle.isSquare()) {
          const RectanglePosition vPosition = RectanglePosition(Point(j, i), true);
          if(isValid(rectangle, vPosition)) {
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

  bool BoundingBox::isValid(const Rectangle & rectangle,
                            const RectanglePosition & position) const
  {
    if(! isInBox(rectangle, position) ||
       ! hasNoOverlap(rectangle, position))
      return false;

    return true;
  }

  bool BoundingBox::isInBox(const Rectangle & rectangle,
                            const RectanglePosition & position) const
  {
    int rectangleWidth = rectangle.getW();
    int rectangleHeight = rectangle.getH();
    if(position.isVertical()) {
      std::swap(rectangleWidth, rectangleHeight);
    }
    
    // Checks if bounds of rectangle are in the box
    return !(position.getLeftBottomX() + rectangleWidth > width ||
             position.getLeftBottomY() + rectangleHeight > height);
  }

  bool BoundingBox::hasNoOverlap(const Rectangle & rectangle,
                                 const RectanglePosition & position) const
  {
    // We only check for sides of the rectangle: as we place rectangle
    // in decreasing order, there is no way a rectangle could be
    // completely contained in an already placed rectangle, so if
    // sides are free, it does not overlap.

    const std::vector<Point> bounds = position.getSides(rectangle);
    return std::find_if(bounds.begin(), bounds.end(), [this] (Point point) {
        return occupationMatrix.query(point) != -1;
      }) == bounds.end();
  }

  std::list<RectanglePosition> BoundingBox::getSolution() const
  {
    return currentSolution;
  }

  void BoundingBox::checkAndInsertPosition(int i, int j,
                                           const Rectangle & rectangle,
                                           std::deque<RectanglePosition> & result) const
  {
    const RectanglePosition hPosition = RectanglePosition(Point(i, j), false);
    if(isValid(rectangle, hPosition)) {
      result.push_back(hPosition);
    }

    if(! rectangle.isSquare()) {
      const RectanglePosition vPosition = RectanglePosition(Point(i, j), true);
      if(isValid(rectangle, vPosition)) {
        result.push_back(vPosition);
      }
    }
  }
}
