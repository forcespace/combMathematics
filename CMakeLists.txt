cmake_minimum_required(VERSION 3.21)
project(combMathematics)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost 1.74.0 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(narayanaAlgorithm labs/01/1.1/main.cpp)
add_executable(JohnsonTrotterAlgorithm labs/01/1.2/main.cpp)
add_executable(randomPermutations labs/01/1.3/main.cpp)
add_executable(points labs/02/main.cpp)
add_executable(numbers labs/03/main.cpp)
add_executable(combMathematics main.cpp)