cmake_minimum_required(VERSION 3.20)
project(esercitazione2_pcs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(ex1 exx2_ex_1.cpp)
add_executable(ex2 exx2_ex_2.cpp)
