cmake_minimum_required(VERSION 3.2)

project(horner VERSION 0.0.1)

add_executable(horner main.cpp)

set_target_properties(horner PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
target_include_directories(horner
  PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(horner PRIVATE
  -Wall -Wextra -pedantic
)
