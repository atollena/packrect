#include "solution_to_string.hxx"

#include <sstream>
#include <algorithm>

#include "rectangle.hxx"
#include "rectangle_position.hxx"
#include "bounding_box.hxx"


namespace packing {

  /* helper functions */
  static void setPoint(std::vector<std::string> & lines,
                       Point point,
                       char c);

  static std::vector<std::pair<Rectangle, RectanglePosition>>
    zip(const std::vector<Rectangle> & rectangles,
        const std::list<RectanglePosition> & positions);

  namespace {
    std::string concatenateLines(const std::vector<std::string> & lines)
    {
      std::stringstream result;
      for(std::string line : lines) {
        result << line << std::endl;
      }
      return result.str();
    }

    std::string spanHorizontally(const std::string & line)
    {
      std::string result;
      for(auto c: line) {
        result += c;
        result += ' ';
      }
      result.erase(result.end() - 1);
      return result;
    }
  }

  std::string solutionToString (const RectangleSize & box,
                                const std::vector<Rectangle> & rectangles,
                                const std::list<RectanglePosition> & positions)
  {
    std::vector<std::string> lines(box.height,
                                   std::string(box.width, ' '));

    std::vector<std::pair<Rectangle, RectanglePosition>> solution = zip (rectangles,
                                                                         positions);
    solution.reserve(rectangles.size());

    for(auto elem: solution) {
      Rectangle rectangle = elem.first;
      RectanglePosition position = elem.second;

      for(Point point: position.getTopLine(rectangle)) {
        setPoint(lines, point, '-');
      }
      for(Point point: position.getBottomLine(rectangle)) {
        setPoint(lines, point, '-');
      }
      for(Point point: position.getLeftLine(rectangle)) {
        setPoint(lines, point, '|');
      }
      for(Point point: position.getRightLine(rectangle)) {
        setPoint(lines, point, '|');
      }
      setPoint(lines, position.getLeftBottom(), '+');
      setPoint(lines, position.getBottomRight(rectangle), '+');
      setPoint(lines, position.getTopRight(rectangle), '+');
      setPoint(lines, position.getTopLeft(rectangle), '+');
    }

    std::vector<std::string> spannedLines;
    spannedLines.resize(lines.size());
    std::transform(lines.begin(), lines.end(), spannedLines.begin(),
                   spanHorizontally);
    
    return concatenateLines(spannedLines);
  }

  static void setPoint(std::vector<std::string> & lines,
                       Point point,
                       char c)
  {
    lines[point.getY()][point.getX()] = c;
  }

  static std::vector<std::pair<Rectangle, RectanglePosition>>
                  zip(const std::vector<Rectangle> & rectangles,
                      const std::list<RectanglePosition> & positions) {
    std::vector<std::pair<Rectangle, RectanglePosition>> solution;

    auto position = positions.begin();

    auto rectangle = rectangles.begin();
    while(position != positions.end() && rectangle != rectangles.end()){
      solution.push_back(std::make_pair(*rectangle, *position));
      ++position;
      ++rectangle;
    }
    return solution;
  }
}
