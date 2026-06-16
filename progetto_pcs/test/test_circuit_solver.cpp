#include "circuit_solver.hpp"
#include "component.hpp"
#include "cycle_basis.hpp"
#include <iostream>
#include <optional>
#include <vector>
#include <cmath> // Serve per std::abs nei controlli numerici

int main() {
    std::cout << "--- Inizio Test Solutore Elettrico ---" << std::endl;

    // Creo a mano un circuito semplice: un generatore da 10V e una resistenza da 5 Ohm in parallelo tra i nodi 1 e 2
    std::vector<Component> components = {
        {"V1", 10.0, 1, 2}, 
        {"R1", 3.0,  2, 3}, 
        {"R2", 2.0,  1, 3}  
    };

    // Costruisco la maglia inserendo direttamente gli indici degli archi per fare un test isolato del solutore
    OrientedCycle maglia;
    maglia.push_back({0, 1});  // V1: percorso da 1 a 2 (concorde all'arco, segno 1)
    maglia.push_back({1, 1});  // R1: percorso da 2 a 3 (concorde all'arco, segno 1)
    maglia.push_back({2, -1}); // R2: percorso da 3 a 1 (discorde all'arco 1->3, segno -1)

    std::vector<OrientedCycle> maglie = {maglia};

    // Lancio il calcolo del circuito
    auto tensioni_res = risolvi_circuito(components, maglie);
    
    // Controllo di sicurezza sull'optional
    if (!tensioni_res.has_value()) {
        std::cerr << "[ERRORE TEST]: Il solutore ha restituito nullopt (mancata convergenza o matrice non SPD)." << std::endl;
        return 1;
    }

    // Estraggo la mappa reale
    std::map<std::string, double> tensioni = tensioni_res.value();
    
    // Verifico che la resistenza R1 sia presente nella mappa dei risultati
    if (tensioni.find("R1") == tensioni.end()) {
        std::cerr << "[ERRORE TEST]: Il solutore non ha calcolato il valore per R1." << std::endl;
        return 1;
    }

    double tensione_r1 = tensioni["R1"];
    double tensione_r2 = tensioni["R2"];

    // Calcolo le correnti con la legge di Ohm sui rami ordinati
    double corrente_r1 = tensione_r1 / 3.0;
    double corrente_r2 = tensione_r2 / 2.0;

    // Attesi: V_R1 = -6.0 V, I_R1 = -2.0 A | V_R2 = 4.0 V, I_R2 = 2.0 A
    if (std::abs(tensione_r1 - (-6.0)) > 1e-5 || std::abs(corrente_r1 - (-2.0)) > 1e-5) {
        std::cerr << "[ERRORE TEST]: Calcolo su R1 fallito. V = " << tensione_r1 << ", I = " << corrente_r1 << std::endl;
        return 1;
    }

    if (std::abs(tensione_r2 - 4.0) > 1e-5 || std::abs(corrente_r2 - 2.0) > 1e-5) {
        std::cerr << "[ERRORE TEST]: Calcolo su R2 fallito. V = " << tensione_r2 << ", I = " << corrente_r2 << std::endl;
        return 1;
    }

    std::cout << "[OK]: Test del solutore superato con successo." << std::endl;
    return 0;
}