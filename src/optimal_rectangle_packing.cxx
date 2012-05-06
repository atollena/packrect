#include <algorithm>
#include <cassert>

#if !defined NDEBUG || defined STATISTICS
#include <iostream>
#endif

#include "optimal_rectangle_packing.hxx"
#include "rectangle_containment_solver.hxx"
#include "rectangle.hxx"

namespace packing {

  OptimalRectanglePacking::OptimalRectanglePacking(const std::vector<Rectangle> & input)
    : input(input)
#ifdef STATISTICS
    , backtrackNodes(0)
#endif
  {
    // Rectangles must be sorted in decreasing order of width for the
    // containment solving algorithm to be applied
    std::sort(this->input.begin(), this->input.end(), Rectangle::BiggerWidth());
  }

  Solution OptimalRectanglePacking::compute()
  {
    std::deque<RectangleSize> boxSizes = candidateBoxSizes();

    /*
     * Sort bounding boxes in non-decreasing order of areas. By doing
     * this, we make sure that the first box that has a solution for
     * the rectangle containment problem is the smaller bounding
     * box. If we wouldn't sort it, we could easily transform the
     * algorithm in an anytime algorithm, as the front() of boxSizes
     * was determined using a greedy algorithm and definetly is a
     * valid packing.  The algorithm here finds the best solution
     * faster, but can't give a solution "anytime".
     */
    std::sort(boxSizes.begin(), boxSizes.end(),
              RectangleSize::SmallerArea());

    std::deque<RectangleSize>::const_iterator box = boxSizes.begin();

    std::list<RectanglePosition> solution = solveRectangleContainment(*box);

    while (solution.empty()) {
      ++box;
      assert(box != boxSizes.end()); /* We have the greedy solution to
                                        prevent that */
      solution = solveRectangleContainment(*box);
    }

#ifdef STATISTICS
    std::cerr << "Backtrack nodes " << backtrackNodes << std::endl;
#endif

    return Solution(*box, input, solution);
  }

  std::deque<RectangleSize> OptimalRectanglePacking::candidateBoxSizes() const
  {
    // Computes a box containing all rectangles and having this height
    RectangleSize startBox = greedyRectanglePacker();

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
    std::deque<RectangleSize> result;
    result.push_back(startBox);
    for(int height = startBox.height;
        height <= startBox.width;
        ++height) {
      for(int width = startBox.width;
          height * width >= minArea && height <= width;
          --width) {
        if(height * width < startBox.computeArea() ) {
          result.push_back(RectangleSize(width, height));
        }
      }
    }

    return result;
  }

  RectangleSize OptimalRectanglePacking::greedyRectanglePacker() const
  {
    // Get the smallest possible height for the bounding box, which is
    // the height of the highest rectangle
    int smallestHeight = std::min_element(input.begin(), input.end(),
                                          Rectangle::BiggerHeight())->getH();

    // Returns the bounding box containing all rectangles put flat
    // next to another.
    return RectangleSize(std::accumulate(input.begin(),
                                         input.end(), 0,
                                         [] (int current, Rectangle rectangle) {
                                           return current + rectangle.getW();
                                         }), smallestHeight);

    // A possible improvement could be to place rectangles higher as
    // soon as a place is available.
  }

  std::list<RectanglePosition>
  OptimalRectanglePacking::solveRectangleContainment(const RectangleSize & boxSize)
  {
#ifndef NDEBUG
    std::cerr << "Testing box " << boxSize.width << "*"
              << boxSize.height << std::endl;
#endif

    auto solver = RectangleContainmentSolver(Invariants(input), boxSize);
    std::list<RectanglePosition> solution = solver.compute();

#ifdef STATISTICS
    backtrackNodes += solver.backtrackNodes;
#endif

    return solution;
  }
}
