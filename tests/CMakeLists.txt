# Unit tests definition
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gtest_INCLUDE_DIRS})
add_executable (runUnitTests
  ${gtest_SOURCE_DIR}/src/gtest_main.cc
  optimal_rectangle_packing_tests.cxx
  rectangle_containment_solver_tests.cxx
  rectangle_tests.cxx
  box_occupation_matrix_tests.cxx)
target_link_libraries(runUnitTests packer gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
add_test (
  NAME runUnitTests
  COMMAND runUnitTests
  )
