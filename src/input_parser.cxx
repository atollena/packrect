#include "input_parser.hxx"

namespace packing {

  std::vector<Rectangle> parseInput(std::istream & input)
  {
    int nRectangles;
    input >> nRectangles;

    std::vector<Rectangle> result;
    for(int i = 0; i < nRectangles; ++i) {
      int width, height;
      input >> width;
      input >> height;

      // Rectangle width must be bigger than height
      if(height > width) {
        std::swap(width, height);
      }
      
      result.push_back(Rectangle(width, height, i));
    }

    return result;
  }
  
}
