#include "solution_to_string.hxx"

#include <sstream>
#include <algorithm>

#include "helper.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "bounding_box.hxx"

namespace packing {

  /* helper class */
  namespace {
    class SolutionDrawer {
    public:
      SolutionDrawer(const RectangleSize & size)
        : lines(size.height,
                std::string(size.width * 2 - 1, ' '))
      {}

      /**
       * Draw `rectangle` at `position` into `lines`.  Note that strings
       * contained in `lines` must be of sufficient size.
       */
      void drawRectangle(Rectangle rectangle,
                         RectanglePosition position)
      {
        // First draw the sides
        drawPoints(position.getTopLine(rectangle), '-');
        drawPoints(position.getBottomLine(rectangle), '-');
        drawPoints(position.getLeftLine(rectangle), '|');
        drawPoints(position.getRightLine(rectangle), '|');

        // Then the corners
        drawPoint(position.getLeftBottom(), '+');
        drawPoint(position.getBottomRight(rectangle), '+');
        drawPoint(position.getTopRight(rectangle), '+');
        drawPoint(position.getTopLeft(rectangle), '+');
      }
      /**
       * Concatenate all strings contained in `lines`, separated by an
       * end of line character.
       */
      std::string output() const
      {
        std::stringstream result;
        for(std::string line : lines) {
          result << line << std::endl;
        }

        return result.str();
      }

    private:
      /**
       * Sets position `point` in `lines` to `c`
       */
      void drawPoint(Point point,
                     char c)
      {
        // makes the string more spanned horizontally by writing only
        // one character of two.
        lines[point.getY()][2 * point.getX()] = c;
      }

      /**
       * Draw a set of points using the given character
       */
      void drawPoints(const std::vector<Point> & points,
                      char c)
      {
        for(Point point: points) {
          drawPoint(point, c);
        }
      }

      std::vector<std::string> lines; // Store the content
    };
  }

  std::string solutionToString (const RectangleSize & box,
                                const std::vector<Rectangle> & rectangles,
                                const std::list<RectanglePosition> & positions)
  {
    SolutionDrawer drawer(box);

    /* Construct a vector of pair to allow iterating on both vectors
     * at the same time */
    std::vector<std::pair<Rectangle, RectanglePosition>> solution =
      zip (rectangles,
           positions);

    for(auto elem: solution) {
      drawer.drawRectangle(elem.first, elem.second);
    }

    return drawer.output();
  }
}
