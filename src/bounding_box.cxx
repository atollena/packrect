#include <cassert>
#include <algorithm>

#include "bounding_box.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "wasted_space_pruner.hxx"

namespace packing {
  BoundingBox::BoundingBox(const RectangleSize & size)
    :size(size), occupationMatrix(size)
  {
    assert(size.width > 0 && size.height > 0);
  }

  int BoundingBox::computeArea() const
  {
    return size.computeArea();
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
    int xMax = (size.width - 1) / 2 + 1;
    int yMax = (size.height - 1) / 2 + 1;

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
    for(int i = 0; i < size.height; i++) {
      for(int j = 0; j < size.width; j++) {
       checkAndInsertPosition(j, i, rectangle, result);
      }
    }
    return result;
  }

  bool BoundingBox::isPruned(std::vector<Rectangle>::const_iterator first,
                             std::vector<Rectangle>::const_iterator last,
                             int totalRectanglesArea) const
  {
    return WastedSpacePruner()(size, occupationMatrix,
                               first, last, totalRectanglesArea);
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
    return !(position.getLeftBottomX() + rectangleWidth > size.width ||
             position.getLeftBottomY() + rectangleHeight > size.height);
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
