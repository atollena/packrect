#ifndef INPUT_PARSER_CXX
#define INPUT_PARSER_CXX

#include <istream>
#include <vector>

#include "rectangle.hxx"

namespace packing {
  std::vector<Rectangle> parseInput(std::istream & input);
}

#endif // INPUT_PARSER_CXX
