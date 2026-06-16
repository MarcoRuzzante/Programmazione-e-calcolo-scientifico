#include <iostream>
#include <algorithm>   
#include <optional>    

#include "parser.hpp"
#include "graph.hpp"
#include "cycle_basis.hpp"
#include "circuit_solver.hpp"

int main(int argc, char** argv) {
    // Controllo che l'utente abbia passato almeno il file della netlist da terminale
    if (argc < 2) {
        std::cerr << "Errore: Parametri insufficienti.\n"
                  << "Uso: " << argv[0] << " <percorso_netlist> [--dfs|--depina]" << std::endl;
        return 1;
    }

    std::string file_netlist = argv[1];
    std::string algoritmo = "--depina"; // Di default uso De Pina per trovare i cicli minimi
    if (argc >= 3) {
        algoritmo = argv[2]; // Se specificato, accetto la scelta dell'algoritmo (--dfs o --depina)
    }

    // Verifico che il flag inserito sia uno dei due consentiti dal bando
    if (algoritmo != "--dfs" && algoritmo != "--depina") {
        std::cerr << "Errore: Algoritmo non riconosciuto. Usa '--dfs' o '--depina'" << std::endl;
        return 1;
    }

    // Leggo l'optional restituito dal parser
    auto componenti_res = leggi_netlist(file_netlist);
    
    // Verifico se l'optional è vuoto (fallimento del parser) o se il vettore interno è vuoto
    if (!componenti_res.has_value() || componenti_res.value().empty()) {
        std::cerr << "Errore: Netlist vuota, malformata o file non accessibile." << std::endl;
        return 1;
    }
    
    // Estraggo il vector reale. In questo modo "componenti" torna a essere un std::vector
    std::vector<Component> componenti = componenti_res.value();

    undirected_graph<int> rete;
    std::map<undirected_edge<int>, double> pesi;

    // Scorro i componenti per costruire il grafo e validare i vincoli del circuito
    for (const auto& comp : componenti) {
        
        // Controllo se il nodo iniziale è uguale a quello finale
        if (comp.node_from == comp.node_to) {
            std::cerr << "Errore: Il componente " << comp.id 
            << " genera un autoanello sul nodo " << comp.node_from << std::endl;
            return 1;
        }

        // Controllo se esiste già un componente tra gli stessi due nodi (i paralleli sono vietati)
        undirected_edge<int> arco(comp.node_from, comp.node_to);
        if (!rete.add_edge(arco)) {
            std::cerr << "Errore: Rilevato parallelo tra i nodi " 
            << comp.node_from << " e " << comp.node_to << std::endl;
            return 1;
        }

        // Assegno i pesi agli archi per l'algoritmo di De Pina
        if (comp.id[0] == 'R' || comp.id[0] == 'r') {
            // Una resistenza deve essere strettamente positiva
            if (comp.value <= 0) {
                std::cerr << "Errore Fisico: Il resistore " << comp.id 
                          << " ha un valore non valido (R = " << comp.value << "). Deve essere > 0." << std::endl;
                return 1;
            }
            pesi[arco] = comp.value; // Il peso dell'arco corrisponde al valore in Ohm della resistenza
        } else {
            // Ai generatori assegno un peso quasi nullo per fare in modo che Dijkstra non rimanga intrappolato in loop
            pesi[arco] = 1e-6; 
        }
    }

    undirected_graph<int> albero_copertura;
    std::vector<undirected_edge<int>> archi_rimanenti;
    std::vector<BinaryVector> vettori_binari; 
    
    // Scompongo il grafo in albero di copertura e coalbero (archi rimanenti)
    if (!trova_albero_e_coalbero(rete, albero_copertura, archi_rimanenti, vettori_binari)) {
        std::cerr << "Errore! Le specifiche del file.net non soddisfano i requisiti.\n\n" << std::endl;
        return 1; 
    }

    std::vector<OrientedCycle> maglie;
    // Scelta dell'algoritmo per l'estrazione della base dei cicli
    if (algoritmo == "--dfs") {
        std::cout << "\nCalcolo cicli fondamentali con DFS..." << std::endl;
        maglie = cicli_fondamentali_dfs(rete, albero_copertura, archi_rimanenti);
    } else {
        std::cout << "\nCalcolo cicli minimi con De Pina..." << std::endl;
        maglie = de_pina(rete, pesi, vettori_binari);
    }

    // Risolvo il sistema lineare per ricavare il vettore delle tensioni sui resistori
    auto tensioni_res = risolvi_circuito(componenti, maglie);
    if (!tensioni_res.has_value()) {
        std::cerr << "Errore: Impossibile calcolare le tensioni del circuito." << std::endl;
        return 1; 
    }
    
    // Estraggo la mappa reale per la stampa finale
    std::map<std::string, double> tensioni = tensioni_res.value();
    // Stampo i risultati finali calcolando la corrente tramite la legge di Ohm: I = V / R
    std::cout << "\n--- Risultati Analisi Circuito ---" << std::endl;
    for (const auto& comp : componenti) {
        if (comp.id[0] == 'R' || comp.id[0] == 'r') {
            double v = tensioni[comp.id];      
            double current = v / comp.value;         
            std::cout << comp.id << ": V = " << v << " volts, I = " << current << " amps." << std::endl;
        }
    }

    return 0; 
}