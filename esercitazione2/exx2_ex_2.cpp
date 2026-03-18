#include <iostream>
#include <cmath>

int main(){

    static const int N = 10;
    double arr[N] = {0.0,-1.4,3.2,7.8,-2.3,5.0,2.1,19.3,-12.5,3.2};

    double min = arr[0];
    double max = arr[0];
    double somma = arr[0];

    for(int i = 1;i < N;i++){

        min = std::min(min,arr[i]);
        max = std::max(max,arr[i]);
        somma += arr[i];

    }

    double media = somma / N;
    double somma_dev_standard = 0.0;

    for(int i = 0;i < N;i++){

        somma_dev_standard += ((arr[i] - media)*(arr[i]-media));

    }       

    double dev_standard = std::sqrt((somma_dev_standard/N));

    std::cout <<"\nIl valore minimo è: "<<min;
    std::cout <<"\nIl valore massimo è: "<<max;
    std::cout <<"\nLa media è: "<<media;
    std::cout <<"\nLa deviazione standard è: "<<dev_standard;

    bool F = true;

    while(F){

        F = false;
        for(int i = 0; i< N-1; i++){

            if(arr[i] > arr[i+1]){

                F = true;
                double scambio = arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=scambio;

            }

        }

    }

    std::cout <<"\n\nOrdinamento vettore con l'algoritmo bubble-sort:\n";
    for(int i = 0; i<N; i++){

        std::cout <<"Stampa elemento posizione " << i <<": "<<arr[i]<<"\n";

    }
    std::cout <<"\n";

}