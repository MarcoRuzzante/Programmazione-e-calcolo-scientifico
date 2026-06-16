#pragma once
#include <string>

// Struttura che rappresenta un singolo componente del circuito elettrico
struct Component {
    std::string id;   // Identificatore del componente (es. "R1", "V1")
    double value;     // Valore (Resistenza in Ohm o Tensione in Volt)
    int node_from;    // Nodo di inizio (morsetto positivo per i generatori)
    int node_to;      // Nodo di fine (morsetto negativo per i generatori)
};