#include "graph.hpp"
#include <set>
#include <map>
#include <vector>

template <typename T>
struct nodo_distanza {
    double dist;
    T nodo;

    bool operator<(const nodo_distanza& other) const {
        if (dist != other.dist) {
            return dist < other.dist;
        }
        return nodo < other.nodo;
    }
};

template <typename T, typename Container>
undirected_graph<T> graph_visit(const undirected_graph<T>& G, const T& source, Container& c) {
    undirected_graph<T> tree;
    std::set<T> visited;

    c.put(source);
    visited.insert(source);

    while (!c.empty()) {
        T curr = c.get();
        
        for (const T& neighbor : G.neighbours(curr)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                tree.add_edge(undirected_edge<T>(curr, neighbor));
                c.put(neighbor);
            }
        }
    }
    return tree;
}

template <typename T>
void dfs_recursive_helper(const undirected_graph<T>& G, const T& u, std::set<T>& visited, undirected_graph<T>& tree) {
    
    std::vector<T> da_visitare; 

    for (const T& v : G.neighbours(u)) {

        if (visited.find(v) == visited.end()) {
            visited.insert(v); 
            tree.add_edge(undirected_edge<T>(u, v));
            da_visitare.push_back(v);
        }
    }

    for (int i = (int)da_visitare.size() - 1; i >= 0; i--) {
        dfs_recursive_helper(G, da_visitare[i], visited, tree);
    }
}

template <typename T>
undirected_graph<T> recursive_dfs(const undirected_graph<T>& G, const T& source) {
    undirected_graph<T> tree;
    std::set<T> visited;

    visited.insert(source);
    
    dfs_recursive_helper(G, source, visited, tree);

    return tree;
}

template <typename T>
std::map<T, double> dijkstra(const undirected_graph<T>& G, const T& source, undirected_graph<T>& spt, const std::map<undirected_edge<T>, double>& weights) {
    
    std::map<T, double> distances;
    std::set<nodo_distanza<T>> pq; 
    std::map<T, T> parent; 
    
    distances[source] = 0.0;
    
    nodo_distanza<T> start_node;
    start_node.dist = 0.0;
    start_node.nodo = source;
    pq.insert(start_node);

    while (!pq.empty()) {
        auto it = pq.begin();
        double current_dist = it->dist;
        T u = it->nodo;
        pq.erase(it);

        if (current_dist > distances.at(u)) continue;

        for (const T& v : G.neighbours(u)) {
            undirected_edge<T> edge(u, v);
            double weight = weights.count(edge) ? weights.at(edge) : 1.0; 

            bool v_is_infinity = (distances.find(v) == distances.end());
            
            if (v_is_infinity || distances.at(u) + weight < distances.at(v)) {
                if (!v_is_infinity) {
                    nodo_distanza<T> old_record;
                    old_record.dist = distances.at(v);
                    old_record.nodo = v;
                    pq.erase(old_record);
                }
                
                distances[v] = distances.at(u) + weight;
                parent[v] = u; // Salviamo l'arco del cammino minimo
                
                nodo_distanza<T> new_record;
                new_record.dist = distances.at(v);
                new_record.nodo = v;
                pq.insert(new_record);
            }
        }
    }

    for (const auto& p : parent) {
        spt.add_edge(undirected_edge<T>(p.second, p.first));
    }

    return distances;
}