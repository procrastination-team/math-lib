cmake_minimum_required(VERSION 3.2)

project(math-lib VERSION 0.0.1)

add_executable(horner_scheme horner_scheme/main.cpp)
add_executable(gauss_determinant gauss_determinant/main.cpp)
add_executable(complex_matrices complex_matrices/main.cpp)
add_executable(vector_multiplication vector_multiplication/main.cpp)
add_executable(fourier_transform fourier_transform/main.cpp)
add_executable(interpolate Gauß-interpolation/main.cpp)

set_target_properties(horner_scheme PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
target_include_directories(horner_scheme
  PRIVATE horner_scheme
)
target_compile_options(horner_scheme PRIVATE
  -Wall -Wextra -pedantic
)


set_target_properties(complex_matrices PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)
target_include_directories(complex_matrices
  PRIVATE common
)
target_compile_options(complex_matrices PRIVATE
  -Wall -Wextra -pedantic
)


target_compile_options(vector_multiplication PRIVATE
  -Wall -Wextra -pedantic
)


set_target_properties(interpolate PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
target_include_directories(interpolate
  PRIVATE common
)
target_compile_options(interpolate PRIVATE
  -Wall -Wextra -pedantic
)

set_target_properties(fourier_transform PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
target_include_directories(fourier_transform
  PRIVATE common
)
target_compile_options(fourier_transform PRIVATE
  -Wall -Wextra -pedantic
)
