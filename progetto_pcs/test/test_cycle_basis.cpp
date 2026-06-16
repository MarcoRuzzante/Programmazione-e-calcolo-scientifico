#include "graph.hpp"
#include "cycle_basis.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "--- Inizio Test Base dei Cicli ---" << std::endl;

    undirected_graph<int> G;
    
    // Costruisco un grafo di prova con 4 nodi e 5 archi
    // Il numero di maglie indipendenti attese è: 5 - 4 + 1 = 2
    G.add_edge(undirected_edge<int>(1, 2)); 
    G.add_edge(undirected_edge<int>(1, 4)); 
    G.add_edge(undirected_edge<int>(2, 3)); 
    G.add_edge(undirected_edge<int>(2, 4)); 
    G.add_edge(undirected_edge<int>(3, 4)); 

    undirected_graph<int> T;
    std::vector<undirected_edge<int>> co_tree;
    std::vector<BinaryVector> S;

    // Eseguo la scomposizione del grafo per isolare l'albero e il coalbero
    if (!trova_albero_e_coalbero(G, T, co_tree, S)) {
        std::cerr << "[ERRORE TEST]: Calcolo di albero e coalbero fallito." << std::endl;
        return 1;
    }

    // Controllo che il numero di corde nel coalbero sia esattamente pari al numero di maglie indipendenti (2)
    if (co_tree.size() != 2) {
        std::cerr << "[ERRORE TEST]: Numero di corde errato. Trovate: " << co_tree.size() << " (Attese: 2)" << std::endl;
        return 1;
    }

    // Controllo che il vettore S contenga 2 vettori (uno per corda) e che ognuno sia lungo quanto tutti gli archi (5)
    if (S.size() != 2 || S[0].size() != 5) {
        std::cerr << "[ERRORE TEST]: Dimensioni dei vettori di supporto S sbagliate." << std::endl;
        return 1;
    }

    std::cout << "[OK]: Test base dei cicli superato." << std::endl;
    return 0;
}