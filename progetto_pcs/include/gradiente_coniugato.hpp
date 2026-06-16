#pragma once
#include <iostream>
#include <Eigen/Dense> 
#include <optional>    

inline std::optional<Eigen::VectorXd> gradiente_coniugato(const Eigen::MatrixXd& A, 
                                                          const Eigen::VectorXd& b, 
                                                          const Eigen::VectorXd& x0, 
                                                          double tolleranza) {
    
    // Check di sicurezza: la matrice deve essere quadrata per poter risolvere il sistema
    if (A.rows() != A.cols()) {
        std::cerr << "Errore: La matrice A non è quadrata." << std::endl;
        return std::nullopt;
    }

    // Controllo numerico: verifico se la matrice è simmetrica (A deve essere uguale alla sua trasposta)
    if (!A.isApprox(A.transpose(), 1e-12)) { 
        std::cerr << "Errore: La matrice A non è simmetrica." << std::endl;
        return std::nullopt;
    }
    
    Eigen::VectorXd x = x0;
    
    // Calcolo il residuo iniziale con la formula: r = b - A*x
    Eigen::VectorXd r = b - A * x; 
    
    // All'inizio, la prima direzione di ricerca p coincide esattamente con il residuo r
    Eigen::VectorXd p = r;
    
    double norm_r0 = r.norm();
    
    // Se il sistema è già praticamente risolto all'inizio, ritorno subito la x0 senza fare calcoli
    if (norm_r0 < 1e-15) {
        return x;
    }
    
    double rho = r.squaredNorm(); // Calcolo la norma al quadrato del residuo (ci serve per i passi successivi)
    int k = 0;
    int n = A.rows();
    
    // Ciclo principale: mi fermo se supero il numero massimo di passi (n) o se l'errore scende sotto la tolleranza
    while (k < n && r.norm() > tolleranza * norm_r0) {
        
        Eigen::VectorXd Ap = A * p; 
        
        // Controllo se la matrice è definita positiva: il prodotto p^T * A * p deve essere maggiore di zero
        double p_Ap = p.dot(Ap); 
        if (p_Ap < 1e-12) {
            std::cerr << "Errore: La matrice non è definita positiva." << std::endl;
            return std::nullopt; 
        }
        
        // Calcolo la lunghezza del passo ottimale alpha lungo la direzione corrente
        double alpha = rho / p_Ap;
        
        // Aggiorno la soluzione x e calcolo il nuovo residuo r di conseguenza
        x += alpha * p;
        r -= alpha * Ap;
        
        // Calcolo il nuovo fattore beta che serve a rendere la prossima direzione coniugata (ortogonale) alle precedenti
        double rho_nuovo = r.squaredNorm();
        double beta = rho_nuovo / rho;
        
        // Aggiorno la direzione di ricerca p per il prossimo passo del ciclo
        p = r + beta * p;
        
        rho = rho_nuovo;
        k++;
    }
    
    return x;
}