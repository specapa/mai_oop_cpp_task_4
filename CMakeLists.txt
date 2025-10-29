cmake_minimum_required(VERSION 3.15)
project(mai_oop_cpp_task_4)
add_definitions(-w)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

add_library(figure_lib INTERFACE)
target_include_directories(figure_lib INTERFACE include)
target_include_directories(figure_lib INTERFACE templates)
add_executable(lab04 src/main.cpp)
target_link_libraries(lab04 figure_lib)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_template tests/test_template.cpp)
target_link_libraries(test_template PRIVATE figure_lib gtest_main)
add_test(NAME FigureTests COMMAND test_template)