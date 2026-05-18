cmake_minimum_required(VERSION 3.20)
project(esercitazione9)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

enable_testing()

add_executable(test_edge test_edge.cpp)
add_test(NAME Edge_Unit_Test COMMAND test_edge)

add_executable(test_graph test_graph.cpp)
add_test(NAME Graph_Unit_Test COMMAND test_graph)

add_executable(test_es9 test_es9.cpp)
add_test(NAME Esercitazione9_Test COMMAND test_es9)