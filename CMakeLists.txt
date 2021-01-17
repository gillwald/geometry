cmake_minimum_required(VERSION 2.6)

project(gillwald-geometry)

add_compile_options(-std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers)

find_package(GTest REQUIRED)
include_directories(third_party include ${GTEST_INCLUDE_DIRS})
add_library(liblodepng third_party/lodepng/lodepng.cpp)

add_library(gillwald_geometry src/geometry.cpp)

target_link_libraries(gillwald_geometry liblodepng)

add_executable(geometry_tests test/geometry_tests.cpp)
target_link_libraries(geometry_tests
  ${GTEST_LIBRARIES}
  gmock
  pthread
  gillwald_geometry)

# include_directories(third_party)
add_library(gillwald_pngEncodeDecode src/pngEncodeDecode.cpp third_party/lodepng/lodepng.cpp)
add_executable(pngEncodeDecode_tests test/pngEncodeDecode_tests.cpp)
target_link_libraries(pngEncodeDecode_tests
  ${GTEST_LIBRARIES}
  gmock
  pthread
  gillwald_pngEncodeDecode)