# Unit tests definition
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gtest_INCLUDE_DIRS})
add_executable (runUnitTests optimal_rectangle_packing_tests.cxx)
target_link_libraries(runUnitTests packer gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
add_test (
  NAME runUnitTests
  COMMAND runUnitTests
  )
