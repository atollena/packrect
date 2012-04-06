# Solution program
add_library (packer STATIC rectangle.cxx optimal_rectangle_packing.cxx)
add_executable (packrect packing_main.cxx)
