#include <iostream>
#include <vector>
#include <algorithm>

#include "sorts.h"
#include "randfiller.h"
#include "timecounter.h"

int main(void){
    randfiller rf;
    timecounter tc;

    for (int dim = 4; dim <= 8192; dim *= 2) {
        std::vector<double> originale;          //creo una copia dell'originale così da avere la versione non ordinata fissa
        originale.resize(dim);
        rf.fill(originale, -100.0, 100.0);

        std::vector<double> vb = originale;
        std::vector<double> vi = originale;
        std::vector<double> vs = originale;
        std::vector<double> vstd = originale;

        tc.tic();
        bubble_sort(vb);
        double time_bubble = tc.toc();

        tc.tic();
        insertion_sort(vi);
        double time_insertion = tc.toc();

        tc.tic();
        selection_sort(vs);
        double time_selection = tc.toc();

        tc.tic();
        std::sort(vstd.begin(), vstd.end());
        double time_std = tc.toc();

        std::cout << dim << "\t" << time_bubble << "\t" << time_insertion << "\t" << time_selection << "\t" << time_std << "\n";
    }

    return EXIT_SUCCESS;
}