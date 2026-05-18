#include <iostream>
#include "graph.hpp"

int main() {

    undirected_graph<int> G1;
    
    G1.add_edge(undirected_edge<int>(1, 2));
    G1.add_edge(undirected_edge<int>(2, 3));
    G1.add_edge(undirected_edge<int>(3, 1));
    G1.add_edge(undirected_edge<int>(4, 5));

    if (G1.all_nodes().size() != 5) {
        return EXIT_FAILURE;
    }

    if (G1.all_edges().size() != 4) {
        return EXIT_FAILURE;
    }

    if (G1.neighbours(2).size() != 2) {
        return EXIT_FAILURE;
    }

    undirected_edge<int> search_edge(2, 3);
    std::size_t id_arco = G1.edge_number(search_edge); 
    undirected_edge<int> retrieved_edge = G1.edge_at(id_arco);
    
    if (!(retrieved_edge == search_edge)) {
        return EXIT_FAILURE;
    }

    undirected_graph<int> G2;
    G2.add_edge(undirected_edge<int>(1, 2));
    G2.add_edge(undirected_edge<int>(4, 5));

    undirected_graph<int> G_diff = G1 - G2;
    
    if (G_diff.all_edges().size() != 2) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}