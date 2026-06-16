cmake_minimum_required(VERSION 3.20)
project(SolutoreCircuito_PCS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wextra")

find_package(Eigen3 REQUIRED)

# Indica a CMake dove trovare i file Header (.hpp)
include_directories(include)


add_executable(circuit_solver
    src/main.cpp
    src/parser.cpp
    src/circuit_solver.cpp
)
target_link_libraries(circuit_solver PRIVATE Eigen3::Eigen)

enable_testing()

# Test 1: Basi dei cicli e topologia di rete
add_executable(test_base_cicli test/test_cycle_basis.cpp src/circuit_solver.cpp src/parser.cpp)
target_link_libraries(test_base_cicli PRIVATE Eigen3::Eigen)
add_test(NAME TestBaseCicli COMMAND test_base_cicli)

# Test 2: Lettura e interpretazione del file di testo (Parser)
add_executable(test_lettura test/test_parser.cpp src/parser.cpp)
add_test(NAME TestParser COMMAND test_lettura)

# Test 3: Solutore del sistema lineare (Gradiente Coniugato)
add_executable(test_algoritmi test/test_gradiente_coniugato.cpp)
target_link_libraries(test_algoritmi PRIVATE Eigen3::Eigen)
add_test(NAME TestAlgoritmi COMMAND test_algoritmi)

# Test 4: Risoluzione fisica del circuito elettrico
add_executable(test_circuito test/test_circuit_solver.cpp src/circuit_solver.cpp)
target_link_libraries(test_circuito PRIVATE Eigen3::Eigen)
add_test(NAME TestCircuito COMMAND test_circuito)

# Test 5: Algoritmi di esplorazione e analisi del grafo
add_executable(test_grafi test/test_algorithms.cpp src/circuit_solver.cpp src/parser.cpp)
target_link_libraries(test_grafi PRIVATE Eigen3::Eigen)
add_test(NAME TestAlgoritmiGrafi COMMAND test_grafi)