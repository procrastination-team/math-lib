cmake_minimum_required(VERSION 3.2)

project(test_complex VERSION 0.0.1)

find_package(GTest REQUIRED)

add_executable(test_complex complex_test.cpp)

set_target_properties(test_complex PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(test_complex
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(test_complex GTest::GTest GTest::Main)

target_compile_options(test_complex PRIVATE
  -Wall -Wextra -pedantic -Werror
)

enable_testing()

add_test(test_complex test_complex)
