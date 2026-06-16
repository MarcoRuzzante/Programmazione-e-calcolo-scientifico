#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>    


std::optional<std::vector<Component>> leggi_netlist(const std::string& nome_file) {
    std::vector<Component> componenti; // Vettore in cui salverò tutti i componenti letti dal file
    std::ifstream file(nome_file);     // Apro il file della netlist in modalità lettura

    // Check di sicurezza: se il file non si apre (magari non esiste), avviso ed esco
    if (!file.is_open()) {
        std::cerr << "Errore: impossibile aprire il file " << nome_file << std::endl;
        return std::nullopt; 
    }

    std::string riga;
    // Ciclo principale: leggo il file riga per riga fino a quando non finiscono le righe
    while (std::getline(file, riga)) {
        std::istringstream stream(riga); // Trasformo la riga in uno stream per "spacchettare" i dati
        Component nuovo_comp;
        
        // Provo a estrarre i 4 dati nell'ordine richiesto: ID, Valore, Nodo 1, Nodo 2
        if (stream >> nuovo_comp.id >> nuovo_comp.value >> nuovo_comp.node_from >> nuovo_comp.node_to) {
            componenti.push_back(nuovo_comp); // Se l'estrazione riesce, salvo il componente nel vettore
        } 
        // Se l'estrazione fallisce, devo capire se la riga è solo vuota o se c'è un errore di sintassi
        else {
            bool riga_vuota = true;
            // Controllo ogni singolo carattere della riga fallita
            for (char c : riga) {
                // Se trovo un carattere che non è uno spazio, un tab o un ritorno a capo (\r o \n)
                if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
                    riga_vuota = false; // Allora la riga contiene del testo malformato
                    break;              // Inutile continuare a controllare, esco dal ciclo for
                }
            }
            
            // Se la riga non era vuota ma la lettura è fallita, significa che è un errore vero e proprio
            if (!riga_vuota) {
                std::cerr << "Attenzione: riga malformata rilevata"<< std::endl;
                return std::nullopt;
            }
        }
    }

    return componenti; // Ritorno il vettore con tutti i componenti validi accumulati
}