#include "gradiente_coniugato.hpp"
#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "--- Inizio Test Gradiente Coniugato ---" << std::endl;

    // Definisco una matrice 2x2 simmetrica e definita positiva per fare il test
    Eigen::MatrixXd A(2, 2);
    A << 4.0, 1.0,
         1.0, 3.0;

    // Vettore dei termini noti
    Eigen::VectorXd b(2);
    b << 1.0, 2.0;

    // Imposto il vettore iniziale a zero e scelgo la tolleranza per l'arresto
    Eigen::VectorXd x0 = Eigen::VectorXd::Zero(2);
    double tolleranza = 1e-10;

    // Lancio il solutore per calcolare la soluzione del sistema lineare A * x = b
    auto soluzione = gradiente_coniugato(A, b, x0, tolleranza);

    // Controllo se il solutore è andato a buon fine o se ha fallito la convergenza
    if (!soluzione) {
        std::cerr << "[ERRORE TEST]: Il gradiente coniugato non ha raggiunto la convergenza." << std::endl;
        return 1;
    }

    // Soluzione esatta calcolata analiticamente: x = [1/11, 7/11]
    Eigen::VectorXd x_esatto(2);
    x_esatto << 1.0 / 11.0, 7.0 / 11.0;

    // Verifico se la soluzione calcolata numericamente è quasi uguale a quella esatta
    if (!soluzione.value().isApprox(x_esatto, 1e-6)) {
        std::cerr << "[ERRORE TEST]: La soluzione numerica calcolata è sbagliata." << std::endl;
        return 1;
    }

    std::cout << "[OK]: Test del gradiente coniugato superato con successo." << std::endl;
    return 0;
}