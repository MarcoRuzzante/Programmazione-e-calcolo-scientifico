#include "circuit_solver.hpp"
#include "gradiente_coniugato.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <optional>    
#include <string>
#include <vector>
#include <algorithm>

std::optional<std::map<std::string, double>> risolvi_circuito(const std::vector<Component>& componenti,
                                               const std::vector<OrientedCycle>& maglie) {
    
    int num_resistenze = 0;
    // Array di supporto per dare un indice solo ai resistori. I generatori restano a -1.
    std::vector<int> mappa_resistenze(componenti.size(), -1);       
    
    // Scorro i componenti: se è una resistenza, le assegno un indice progressivo e incremento il conto totale
    for (size_t i = 0; i < componenti.size(); i++) {
        if (componenti[i].id[0] == 'R' || componenti[i].id[0] == 'r') {
            mappa_resistenze[i] = num_resistenze; 
            num_resistenze++; 
        }
    }

    int num_maglie = maglie.size();
    
    // Creo le matrici matematiche del progetto e le azzero con Eigen
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(num_resistenze, num_resistenze); // Matrice diagonale R 
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_resistenze, num_maglie);     // Matrice di incidenza resistenze-maglie
    Eigen::VectorXd v = Eigen::VectorXd::Zero(num_maglie);                     // Vettore dei termini noti dei generatori

    // Riempio la diagonale della matrice R usando i valori in Ohm dei soli resistori 
    for (size_t i = 0; i < componenti.size(); i++) {
        if (mappa_resistenze[i] != -1) {
            R(mappa_resistenze[i], mappa_resistenze[i]) = componenti[i].value;
        }
    }

    // Ciclo su ogni maglia per riempire la matrice B e il vettore v
    for (int j = 0; j < num_maglie; j++) {
        for (const auto& elemento_maglia : maglie[j]) {
            
            size_t id_arco = elemento_maglia.edge_id;
            int segno = elemento_maglia.sign; // Vale +1 se la maglia segue il verso dell'arco, -1 se va al contrario
            const Component& comp = componenti[id_arco]; 

            // CASO 1: Se l'elemento della maglia è una resistenza, popolo la matrice B
            if (comp.id[0] == 'R' || comp.id[0] == 'r') { 
                int r_idx = mappa_resistenze[id_arco];
                B(r_idx, j) = segno; // Metto +1 o -1 a seconda di come la maglia attraversa la resistenza 
            } 
            // CASO 2: Se l'elemento è un generatore, calcolo il suo segno nel termine noto v
            else if (comp.id[0] == 'V' || comp.id[0] == 'v') { 
                
                // Ordino i nodi dal minore al maggiore per adeguarmi alla convenzione standard del grafo 
                int n_min, n_max;
                if (comp.node_from < comp.node_to) {
                    n_min = comp.node_from;
                    n_max = comp.node_to;
                } else {
                    n_min = comp.node_to;
                    n_max = comp.node_from;
                }

                // Capisco quali sono il vero nodo di inizio e fine del cammino in base al segno dell'arco
                int nodo_inizio, nodo_fine;
                if (segno == 1) {
                    nodo_inizio = n_min;
                    nodo_fine = n_max;
                } else {
                    nodo_inizio = n_max;
                    nodo_fine = n_min;
                }

                // comp.node_from è il polo positivo (+).
                // Se entriamo dal polo positivo (nodo_inizio == node_from), il potenziale scende: segno meno (-). 
                if (comp.node_from == nodo_inizio && comp.node_to == nodo_fine) {
                    v(j) -= comp.value; 
                } else {
                    v(j) += comp.value; // Se entriamo dal polo negativo, il potenziale sale: segno più (+).
                }
            }
        }
    }

    // Costruisco la matrice del sistema finale: A = B^T * R * B 
    Eigen::MatrixXd A = B.transpose() * R * B;
    Eigen::VectorXd vettore_iniziale_nullo = Eigen::VectorXd::Zero(num_maglie); 
    
    // Chiamo il solutore del Gradiente Coniugato per calcolare le correnti di maglia 
    std::optional<Eigen::VectorXd> sol = gradiente_coniugato(A, v, vettore_iniziale_nullo, 1e-10);
    
    if (!sol) {
        std::cerr << "Errore: il Gradiente Coniugato non ha raggiunto la convergenza." << std::endl;
        return std::nullopt;
    }

    Eigen::VectorXd correnti_maglie = sol.value();
    // Calcolo le tensioni reali di ogni resistenza usando la formula collettiva della legge di Ohm: V = R * B * i 
    Eigen::VectorXd tensioni_resistenze = R * B * correnti_maglie; 

    // Associo i valori calcolati ai rispettivi nomi delle resistenze per l'output 
    std::map<std::string, double> risultati;
    for (size_t i = 0; i < componenti.size(); i++) {
        if (mappa_resistenze[i] != -1) {
            int r_idx = mappa_resistenze[i];
            risultati[componenti[i].id] = tensioni_resistenze(r_idx); 
        }
    }

    return risultati; 
}