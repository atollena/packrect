# Solution program
add_library (packer STATIC
  rectangle.cxx
  rectangle_position.cxx
  bounding_box.cxx
  rectangle_containment_solver.cxx
  optimal_rectangle_packing.cxx)
add_executable (packrect packing_main.cxx)
