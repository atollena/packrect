cmake_minimum_required (VERSION 2.6)
project (PackingYourDropbox)

set (PROJECT_INCLUDE_DIR include)
set (PROJECT_TESTS_DIR tests)

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Werror -Wextra -pedantic") # Add c++11 functionality
set(CMAKE_CXX_FLAGS_DEBUG "-DSTATISTICS") # Add c++11 functionality

find_package(Threads REQUIRED)

include_directories(${PROJECT_INCLUDE_DIR})

add_subdirectory(gtest)
add_subdirectory(src)
add_subdirectory(tests)


