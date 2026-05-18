#include <iostream>
#include <fstream>
#include <string>
#include "graph.hpp"
#include "adapter.hpp"
#include "algorithms.hpp"

// Funzione di utilità per esportare il grafo per GraphViz
template <typename T>
void export_to_dot(const undirected_graph<T>& G, const std::string& filename) {
    std::ofstream out(filename);
    out << "graph G {\n";
    for (const auto& edge : G.all_edges()) {
        out << "  " << edge.from() << " -- " << edge.to() << ";\n";
    }
    out << "}\n";
}

int main() {
    undirected_graph<int> G;
    
    // Costruzione di un grafo di test
    G.add_edge(undirected_edge<int>(1, 2));
    G.add_edge(undirected_edge<int>(1, 3));
    G.add_edge(undirected_edge<int>(1, 4));
    G.add_edge(undirected_edge<int>(1, 6));
    G.add_edge(undirected_edge<int>(6, 8));
    G.add_edge(undirected_edge<int>(2, 5));
    G.add_edge(undirected_edge<int>(2, 7));
    G.add_edge(undirected_edge<int>(7, 9));
    G.add_edge(undirected_edge<int>(8, 9));
    G.add_edge(undirected_edge<int>(3, 6));
    G.add_edge(undirected_edge<int>(6, 4));
    G.add_edge(undirected_edge<int>(6, 7));
    G.add_edge(undirected_edge<int>(4, 7));
    G.add_edge(undirected_edge<int>(2, 4));
    G.add_edge(undirected_edge<int>(5, 7));

    // 1. Visita BFS 
    fifo<int> q;
    undirected_graph<int> bfs_tree = graph_visit(G, 1, q);
    export_to_dot(bfs_tree, "bfs_tree.dot");

    // 2. Visita DFS iterativa 
    lifo<int> s;
    undirected_graph<int> dfs_tree = graph_visit(G, 1, s);
    export_to_dot(dfs_tree, "dfs_tree.dot");

    // 3. Visita DFS ricorsiva
    undirected_graph<int> dfs_rec_tree = recursive_dfs(G, 1);
    export_to_dot(dfs_rec_tree, "dfs_rec_tree.dot");

    // 4. Dijkstra
    std::map<undirected_edge<int>, double> weights;
    for (const auto& edge : G.all_edges()) {
        weights[edge] = 1.0;
    }

    undirected_graph<int> dijkstra_spt; // Conterrà lo Shortest Path Tree
    std::map<int, double> shortest_paths = dijkstra(G, 1, dijkstra_spt, weights);
    export_to_dot(dijkstra_spt, "dijkstra_tree.dot");

    std::cout << "Distanze calcolate da Dijkstra (Radice = 1):\n";
    for (const auto& pair : shortest_paths) {
        std::cout << "Nodo " << pair.first << " -> Distanza: " << pair.second << "\n";
    }

    return 0;
}