cmake_minimum_required(VERSION 3.17)
project(HW3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
# added -fopenmp

find_package(OpenMP REQUIRED)
add_executable(HW3 main.cpp)
target_link_libraries(HW3 PRIVATE OpenMP::OpenMP_CXX)
