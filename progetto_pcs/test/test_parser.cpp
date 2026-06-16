#include "parser.hpp"
#include "component.hpp"
#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <cstdio>

int main() {
    std::cout << "--- Inizio Test Parser ---" << std::endl;

    std::string file_prova = "circuito_test.net";
    std::ofstream out(file_prova);
    
    // Scrivo nel file una riga vuota (piena di spazi) e una riga con spaziature irregolari
    // per verificare se il parser rispetta i requisiti di robustezza
    out << "V1 12.0 1 2\n";
    out << "    \n"; 
    out << "R1    50.5   2    3\n"; 
    out.close();

    // Inizio la lettura della netlist dal file appena creato
    auto componenti_res = leggi_netlist(file_prova);
    
    std::remove(file_prova.c_str()); 

    // Controllo se il parser ha fallito restituendo nullopt
    if (!componenti_res.has_value()) {
        std::cerr << "[ERRORE]: Il parser ha restituito nullopt (fallimento strutturale)." << std::endl;
        return 1;
    }

    // Estraggo il vettore reale
    std::vector<Component> componenti = componenti_res.value();

    // Controllo che tutti i campi del generatore V1 siano stati salvati correttamente
    if (componenti[0].id != "V1" || componenti[0].value != 12.0 || componenti[0].node_from != 1 || componenti[0].node_to != 2) {
        std::cerr << "[ERRORE]: I dati letti per il generatore V1 sono sbagliati o disallineati." << std::endl;
        return 1;
    }

    // Controllo che tutti i campi del resistore R1 siano stati salvati correttamente
    if (componenti[1].id != "R1" || componenti[1].value != 50.5 || componenti[1].node_from != 2 || componenti[1].node_to != 3) {
        std::cerr << "[ERRORE]: I dati letti per il resistore R1 sono sbagliati o disallineati." << std::endl;
        return 1;
    }

    std::cout << "[OK]: Test del parser superato con successo." << std::endl;
    return 0;
}