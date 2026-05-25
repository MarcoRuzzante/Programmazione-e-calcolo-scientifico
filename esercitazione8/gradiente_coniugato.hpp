#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <optional>     //serve oer returnare nullopt

std::optional<Eigen::VectorXd> gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, double tol) {
    
    // 1. Controllo quadratura 
    if(A.rows() != A.cols()){
        std::cerr << "Errore: la matrice A non è quadrata!" << std::endl;
        return std::nullopt;
    }

    // 2. Controllo simmetria (tolleranza numerica)
    if (!A.isApprox(A.transpose(), 1e-12)){ // controlla con una tolleranza di 1e-12 se A è circa uguale a A'
        std::cerr << "Errore: la matrice A non è simmetrica." << std::endl;
        return std::nullopt;
    }
    
    // 3. Controllo definizione positiva (tutti autovalori > 0)
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(A, Eigen::EigenvaluesOnly);
    if(solver.eigenvalues().minCoeff() < 1e-12){
        std::cerr << "Errore: La matrice non è definita positiva." << std::endl;
        return std::nullopt;
    }

    Eigen::VectorXd x = x0;
    Eigen::VectorXd r = b - A * x;
    Eigen::VectorXd p = r;
    
    double r_norm_0 = r.norm();
    
    unsigned int k = 0;
    
    while (k < A.rows() && r.norm() > tol * r_norm_0) {
    
        /*
        In Eigen, il prodotto tra un vettore riga p.transpose() (1 x n) e un vettore colonna r (n x 1) non restituisce
        un numero primitivo double, ma restituisce  una matrice di dimensioni 1 x 1.
        C++ non permette di assegnare automaticamente una matrice di Eigen a una variabile di tipo double.
        Il metodo .value() applicato a una matrice 1 x 1 di Eigen estrae l'unico coefficiente numerico presente al suo interno, 
        convertendolo nel double puro che serve a noi per l'algoritmo.
        */

        // alpha_k = (p_k^T * r_k) / (p_k^T * A * p_k)
        double alpha_k = ((p.transpose() * r) / (p.transpose() * A*p)).value(); 
        
        // x_{k+1} = x_k + alpha_k * p_k
        x = x + alpha_k * p; 
        
        // r_{k+1} = b - A * x_{k+1}
        Eigen::VectorXd r_next = b - A * x; 
        
        // beta_k = (p_k^T * A * r_{k+1}) / (p_k^T * A * p_k)
        double beta_k = ((p.transpose() * A * r_next) / (p.transpose() * A*p)).value();
        
        // p_{k+1} = r_{k+1} - beta_k * p_k
        p = r_next - beta_k * p;
        
        // Aggiornamento per iterazione successiva
        r = r_next;
        k++;
    }
    
    return x;
}