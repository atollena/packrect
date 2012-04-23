#include <iostream>

#include "input_parser.hxx"
#include "optimal_rectangle_packing.hxx"
#include "solution_to_string.hxx"

int main ()
{
  std::vector<packing::Rectangle> input = packing::parseInput(std::cin);

  auto solution = packing::OptimalRectanglePacking(input).compute();

  std::cout << solution.first.computeArea() << std::endl;

  std::cerr << solution.first.height << "x" << solution.first.width << ":" << std::endl;
  std::cerr << solutionToString(solution.first,
                                input,
                                solution.second);
}
