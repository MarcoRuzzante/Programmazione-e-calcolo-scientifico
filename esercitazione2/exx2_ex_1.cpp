#include <iostream>

int main(){

    double ad[4] = {0.0,1.1,2.2,3.3};
    float af[8] = {0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.7};
    int ai[3] = {0,1,2};

    int x = 1;
    float y = 1.1;

    (&y)[1] = 0;

    /*
    int i = 0;

    std::cout <<"\nStampa degli indirizzi dell'array ad:\n";
    for(i = 0; i < 4; i++){
        std::cout <<"indirizzo di memoria dell'elemento "<<i<<": "<< &ad[i] << "\n";
    }

    std::cout <<"\nStampa degli indirizzi dell'array af:\n";
    for(i = 0; i < 8; i++){
        std::cout <<"indirizzo di memoria dell'elemento "<<i<<": "<< &af[i] << "\n";
    }

    std::cout <<"\nStampa degli indirizzi dell'array ai:\n";
    for(i = 0; i < 3; i++){
        std::cout <<"indirizzo di memoria dell'elemento "<<i<<": "<< &ai[i] << "\n";
    }
    */

    std::cout <<"\nStampa dell'indirizzo di memoria della variabile x: "<< &x << "\n";
    std::cout <<"\nStampa dell'indirizzo di memoria della variabile y: "<< &y << "\n";

    std::cout <<"\nStampa del valore di x: "<< x << "\n";

    return 0;

}