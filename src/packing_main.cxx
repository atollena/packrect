#include <iostream>

#include "input_parser.hxx"
#include "optimal_rectangle_packing.hxx"
#include "solution_to_string.hxx"

int main ()
{
  std::vector<packing::Rectangle> input = packing::parseInput(std::cin);

  auto solution = packing::OptimalRectanglePacking(input).compute();

  std::cout << solution.boxSize.computeArea() << std::endl;

  std::cerr << solution.boxSize.height << "x"
            << solution.boxSize.width << ":" << std::endl;

  std::cerr << solutionToString(solution.boxSize,
                                solution.rectangles,
                                solution.rectanglePositions);
}
