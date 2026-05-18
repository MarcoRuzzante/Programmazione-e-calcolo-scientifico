#include <iostream>
#include "graph.hpp"

int main() {

    undirected_edge<int> e1(5, 2);
    
    // Verifica vincolo (from < to)
    if (e1.from() != 2 || e1.to() != 5) {
        return EXIT_FAILURE;
    }

    undirected_edge<int> e2(2, 5);
    
    if (!(e1 == e2)) {
        return EXIT_FAILURE;
    }

    if ((e1 < e2) || (e2 < e1)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}