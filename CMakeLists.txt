cmake_minimum_required (VERSION 2.6)
project (PackingYourDropbox)

set (PROJECT_INCLUDE_DIR include)
set (PROJECT_TESTS_DIR tests)
AUX_SOURCE_DIRECTORY(src PROJECT_SRC_FILES)

set(CMAKE_CXX_FLAGS "-std=c++0x") # Add c++11 functionality 

include_directories ("${PROJECT_INCLUDE_DIR}")

find_package(Threads REQUIRED)

# Solution program
add_executable (packing-box packing_main.cxx)

# Unit tests definition
enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gtest_INCLUDE_DIRS})
add_executable (runUnitTests ${PROJECT_SRC_FILES} ${PROJECT_TESTS_DIR}/packing_unitTests.cxx)
target_link_libraries(runUnitTests gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
add_test (
  NAME runUnitTests
  COMMAND runUnitTests
  )
