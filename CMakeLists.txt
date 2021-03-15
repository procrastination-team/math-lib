cmake_minimum_required(VERSION 3.2)

project(math-lib VERSION 0.0.1)

add_executable(horner horner_scheme/main.cpp)
add_executable(gauss_det gauss_determinant/mainp.cpp)
add_executable(compl_matrix complex_matrices/main.cpp)

set_target_properties(horner PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
target_include_directories(horner
  PRIVATE horner_scheme
)

target_compile_options(horner PRIVATE
  -Wall -Wextra -pedantic
) 

set_target_properties(compl_matrix PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)
target_include_directories(compl_matrix
  PRIVATE common
)

target_compile_options(compl_matrix PRIVATE
  -Wall -Wextra -pedantic
)
