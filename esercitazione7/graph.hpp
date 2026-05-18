#pragma once

#include <iostream>
#include <map>
#include <set>
#include <list>

using namespace std;

template <typename T>
class undirected_edge {
    T nodo_from; 
    T nodo_to;
public:
    undirected_edge(const T& n1, const T& n2) {
        if (n1 < n2) {
            nodo_from = n1;
            nodo_to = n2;
        } else {
            nodo_from = n2;
            nodo_to = n1;
        }
    }

    const T& from() const { return nodo_from; } 
    const T& to() const { return nodo_to; } 

    bool operator==(const undirected_edge& other) const {
        if (nodo_from == other.nodo_from && nodo_to == other.nodo_to) {
            return true;
        } else {
            return false;
        }
    }

    bool operator<(const undirected_edge& other) const {
        if (nodo_from < other.nodo_from) {
            return true;
        } else if (nodo_from > other.nodo_from) {
            return false;
        } else {
            if (nodo_to < other.nodo_to) {
                return true;
            } else {
                return false;
            }
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream & output, const undirected_edge<T>& e) {
    output << "(" << e.from() << "--" << e.to() << ")";
    return output;
}

template <typename T>
class undirected_graph {

    std::map<T, std::set<T>> lista_adiacenza;
    std::map<undirected_edge<T>, std::size_t> arco_to_id;
    std::map<std::size_t, undirected_edge<T>> id_to_arco;
    std::size_t prossimo_id;
       
public:
    undirected_graph() {
        prossimo_id = 0;
    }

    undirected_graph(const undirected_graph& other) = default; 

    std::set<T> neighbours(const T& nodo) const {
        auto indice_nodo = lista_adiacenza.find(nodo); 
        if (indice_nodo == lista_adiacenza.end()) {
            std::set<T> insieme_vuoto;
            return insieme_vuoto;
        }
        return lista_adiacenza.at(nodo);
    }

    void add_edge(const undirected_edge<T>& arco) {
    
    // risultato_inserimento è un std::pair<iterator, bool>
    auto risultato_inserimento = arco_to_id.insert({arco, prossimo_id});
    
    // Il campo 'second' è il booleano di stato dell'operazione
    if (risultato_inserimento.second) {
        
        // Entriamo qui SOLO se l'arco è stato fisicamente inserito nella mappa arco_to_id.
        
        id_to_arco.insert({prossimo_id, arco});
        
        lista_adiacenza[arco.from()].insert(arco.to());
        lista_adiacenza[arco.to()].insert(arco.from());
        
        prossimo_id++;
    }
}

    std::list<undirected_edge<T>> all_edges() const {

        std::list<undirected_edge<T>> lista_archi;
        for (const auto& pair : arco_to_id) {
            lista_archi.push_back(pair.first);
        }
        return lista_archi;
    }

    std::list<T> all_nodes() const {
        std::list<T> lista_nodi;
        for (const auto& pair : lista_adiacenza) {
            lista_nodi.push_back(pair.first);
        }
        return lista_nodi;
    }

    std::size_t edge_number(const undirected_edge<T>& arco) const {
        return arco_to_id.at(arco);
    }

    undirected_edge<T> edge_at(std::size_t numero) const {
        return id_to_arco.at(numero);
    }

    undirected_graph<T> operator-(const undirected_graph<T>& other) const {
        undirected_graph<T> grafo_finale;

        for (const auto& pair : arco_to_id) {
            undirected_edge<T> arco_corrente = pair.first;
            
            if (other.arco_to_id.find(arco_corrente) == other.arco_to_id.end()) {
                grafo_finale.add_edge(arco_corrente);
            }
        }
        
        return grafo_finale;
    }
};