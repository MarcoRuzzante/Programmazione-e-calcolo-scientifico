#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include "gradiente_coniugato.hpp"

// Funzione per stampare il condizionamento della matrice
double condA(const Eigen::MatrixXd& A) {
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
    Eigen::VectorXd singularValuesA = svd.singularValues();
    return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int main(int argc, char **argv) {
    

    //TEST 1: MATRICE VALIDA (Simmetrica Definita Positiva)
    std::cout << "\nTEST 1: Matrice Simmetrica Definita Positiva" << std::endl;
    unsigned int n = 5;
    
    // Costruzione matrice SPD: A = B^T * B + I 
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
    Eigen::MatrixXd A1 = B.transpose() * B + Eigen::MatrixXd::Identity(n, n);
    
    Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
    Eigen::VectorXd b1 = A1 * x_ex;
    Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
    
    double tol = 1.0e-12; 

    std::cout << "Matrix Cond: " << condA(A1) << std::endl;

    auto res1 = gradiente_coniugato(A1, b1, x0, tol);           //res1 è di tipo std::optional
    //per prendere il valore dovrò usare .value()

    if (res1.has_value()) {
        Eigen::VectorXd x_calc = res1.value();          
        double err_rel = (x_ex.norm() == 0.0) ? (x_calc - x_ex).norm() : (x_calc - x_ex).norm() / x_ex.norm();   

        std::cout.precision(4);
        std::cout << std::scientific << "Errore relativo della soluzione: " << err_rel << std::endl;
    }


    //TEST 2: MATRICE NON SIMMETRICA
    std::cout << "\nTEST 2: Matrice Non Simmetrica" << std::endl;
    Eigen::MatrixXd A2(3,3);
    A2 << 5.0,  2.0, -1.0,
         -2.0,  4.0,  3.0,
         -1.0,  3.0,  7.0; 
    
    Eigen::VectorXd b2 = Eigen::VectorXd::Ones(3);
    Eigen::VectorXd x0_3 = Eigen::VectorXd::Zero(3);

    auto res2 = gradiente_coniugato(A2, b2, x0_3, tol);

    //TEST 3: MATRICE NON DEFINITA POSITIVA
    std::cout << "\nTEST 3: Matrice Non Definita Positiva" << std::endl;
    Eigen::MatrixXd A3(3,3);
    A3 << -4.0,  1.0, -1.0,
           1.0,  3.0,  0.0,
          -1.0,  0.0,  5.0; 

    auto res3 = gradiente_coniugato(A3, b2, x0_3, tol);

    return 0;
}