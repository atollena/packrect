# Solution program
add_library (packer STATIC
  bounding_box.cxx
  box_occupation_matrix.cxx
  empty_strips_tracker.cxx
  input_parser.cxx
  invariants.cxx
  optimal_rectangle_packing.cxx
  rectangle_containment_solver.cxx
  rectangle_position.cxx
  solution_to_string.cxx
  wasted_space_pruner.cxx)
add_executable (packrect packing_main.cxx)
target_link_libraries(packrect packer)
