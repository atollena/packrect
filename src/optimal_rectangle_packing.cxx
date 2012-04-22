#include "optimal_rectangle_packing.hxx"
#include "rectangle_containment_solver.hxx"
#include "rectangle.hxx"

#include <iostream>
#include <algorithm>

namespace packing {

  OptimalRectanglePacking::OptimalRectanglePacking(std::vector<Rectangle> input)
    : input(input)
  {
    std::sort(input.begin(), input.end(), Rectangle::BiggerWidth());
  }

  OptimalRectanglePacking::Packing OptimalRectanglePacking::compute() const
  {
    std::deque<BoundingBox> boxes = candidateBoxes();

    Packing result = std::make_pair(*(boxes.begin()),
                                    RectangleContainmentSolver(input, *(boxes.begin())).compute());
    boxes.pop_front();

    for(BoundingBox box: boxes) {
      if(box.getArea() < result.first.getArea()) {

        std::cerr << "Testing bounding box (" << box.getWidth() << ", "
                  << box.getHeight() << ")" << " area: " << box.getArea() << std::endl;

        std::list<RectanglePosition> solution = RectangleContainmentSolver(input,
                                                                           box).compute();
        if(!solution.empty()) {
          result = std::make_pair(box,
                                  solution);
        }
      }
    }

    return result;
  }

  std::deque<BoundingBox> OptimalRectanglePacking::candidateBoxes() const
  {
    // Computes a box containing all rectangles and having this height
    BoundingBox startBox = greedyRectanglePacker();

    int minArea = std::accumulate(input.begin(),
                                  input.end(), 0,
                                  [] (int current, Rectangle rectangle) {
                                    return current + rectangle.getArea();
                                  });

    /*
     * Generate all ranges of boxes that have an area bigger than sum
     * of areas for all rectangles. As rectangles are not oriented,
     * the problem is symmetric we don't need to check bounding boxes
     * with height <= width, e.g. if we already have tested
     * BoundingBox(5, 3), we don't need to test BoundingBox(3, 5)
     * because the same result would come out.
     *
     * We also filter out bounding boxes that have a bigger area than
     * the startBox, they won't give us a better solution.
     */
    std::deque<BoundingBox> result;
    for(int height = startBox.getHeight();
        height <= startBox.getWidth();
        ++height) {
      for(int width = startBox.getWidth();
          height * width >= minArea && height <= width;
          --width) {
        if(height * width < startBox.getArea() ) {
          result.push_back(BoundingBox(width, height));
        }
      }
    }

    return result;
  }

  BoundingBox
  OptimalRectanglePacking::greedyRectanglePacker() const
  {
    // Get the smallest possible height for the bounding box, which is
    // the height of the highest rectangle
    int smallestHeight = std::min_element(input.begin(), input.end(),
                                          Rectangle::BiggerHeight())->getH();

    // Returns the bounding box containing all rectangles put flat
    // next to another.
    return BoundingBox(std::accumulate(input.begin(),
                                       input.end(), 0,
                                       [] (int current, Rectangle rectangle) {
                                         return current + rectangle.getW();
                                       }), smallestHeight);

    // A possible improvement could be to place rectangles higher as
    // soon as a place is available.
  }
}
