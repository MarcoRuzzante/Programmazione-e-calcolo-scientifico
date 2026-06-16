#include "graph.hpp"
#include "adapter.hpp"
#include "algorithms.hpp"
#include "cycle_basis.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

// Funzione di utilità per costruire un grafo di prova (due quadrati attaccati)
// 5 nodi, 7 archi -> Numero di maglie attese: v = 7 - 5 + 1 = 3
undirected_graph<int> genera_grafo_test() {
    undirected_graph<int> G;
    G.add_edge(undirected_edge<int>(1, 2)); // Arco 0
    G.add_edge(undirected_edge<int>(2, 3)); // Arco 1
    G.add_edge(undirected_edge<int>(3, 4)); // Arco 2
    G.add_edge(undirected_edge<int>(4, 1)); // Arco 3
    G.add_edge(undirected_edge<int>(2, 5)); // Arco 4
    G.add_edge(undirected_edge<int>(5, 4)); // Arco 5
    G.add_edge(undirected_edge<int>(2, 4)); // Arco 6 (diagonale condivisa)
    return G;
}

int main() {
    std::cout << "--- Inizio Test Algoritmi ---" << std::endl;

    undirected_graph<int> G = genera_grafo_test();
    undirected_graph<int> albero_copertura;
    std::vector<undirected_edge<int>> archi_coalbero;
    std::vector<BinaryVector> vettori_supporto;

    // TEST 1: Controllo visite BFS e DFS (tramite le strutture di adapter.hpp)
    fifo<int> coda;
    lifo<int> pila;

    // Se il grafo è connesso, l'albero di copertura deve avere per forza |V| - 1 = 4 archi
    undirected_graph<int> albero_bfs = visita_grafo(G, 1, coda);
    undirected_graph<int> albero_dfs = visita_grafo(G, 1, pila);

    if (albero_bfs.all_edges().size() != 4 || albero_dfs.all_edges().size() != 4) {
        std::cerr << "[ERRORE TEST 1]: Numero di archi sbagliato nelle visite." << std::endl;
        return 1;
    }
    std::cout << "[OK]: Test 1 (Visite BFS e DFS) superato." << std::endl;

    // TEST 2: Calcolo delle maglie fondamentali con la DFS
    if (!trova_albero_e_coalbero(G, albero_copertura, archi_coalbero, vettori_supporto)) {
        std::cerr << "[ERRORE TEST 2]: Calcolo di albero e coalbero fallito." << std::endl;
        return 1;
    }

    std::vector<OrientedCycle> maglie_dfs = cicli_fondamentali_dfs(G, albero_copertura, archi_coalbero);

    // Controllo che il numero di maglie sia corretto: v = 7 - 5 + 1 = 3
    if (maglie_dfs.size() != 3) {
        std::cerr << "[ERRORE TEST 2]: Numero di maglie DFS errato: " << maglie_dfs.size() << " (Attese: 3)" << std::endl;
        return 1;
    }
    std::cout << "[OK]: Test 2 (Maglie fondamentali DFS) superato." << std::endl;

    // TEST 3: Calcolo dei cicli minimi con l'algoritmo di De Pina

    // Svuoto i vettori per evitare di accumulare i vecchi dati calcolati nel Test 2
    archi_coalbero.clear();
    vettori_supporto.clear();

    // Rilancio il calcolo per ripopolare le strutture
    trova_albero_e_coalbero(G, albero_copertura, archi_coalbero, vettori_supporto);


    std::map<undirected_edge<int>, double> pesi;
    std::vector<OrientedCycle> maglie_depina = de_pina(G, pesi, vettori_supporto);

    // 1. Controllo che il numero di maglie sia sempre 3
    if (maglie_depina.size() != 3) {
        std::cerr << "[ERRORE TEST 3]: Numero di maglie De Pina errato: " << maglie_depina.size() << " (Attese: 3)" << std::endl;
        return 1;
    }

    // 2. Controllo che i cicli siano effettivamente corti
    for (const auto& maglia : maglie_depina) {
        if (maglia.size() > 3) {
            std::cerr << "[ERRORE TEST 3]: De Pina ha trovato un ciclo troppo lungo: " << maglia.size() << " archi." << std::endl;
            return 1;
        }
    }
    std::cout << "[OK]: Test 3 (Cicli minimi De Pina) superato." << std::endl;

    std::cout << "TUTTI I TEST SONO PASSATI!" << std::endl;
    return 0;
}