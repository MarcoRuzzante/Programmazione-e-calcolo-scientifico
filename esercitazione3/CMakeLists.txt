cmake_minimum_required(VERSION 3.20)
project(esercitazione3_pcs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(ex1 exx3_ex1.cpp)
add_executable(vec2 vec2.cpp)

