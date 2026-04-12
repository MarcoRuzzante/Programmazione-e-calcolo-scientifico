#include <iostream>
#include <vector>
#include <string>

#include "sorts.h"
#include "randfiller.h"

int main(void){
    randfiller rf;

    for (int i = 0; i < 100; i++) {
        std::vector<double> v;
        v.resize(10);
        rf.fill(v, -100.0, 100.0);

        bubble_sort(v);

        if (!is_sorted(v)) {
            return EXIT_FAILURE;
        }
    }

    std::vector<std::string> vs;
    vs.resize(10);
    vs[0] = "inter";
    vs[1] = "milan";
    vs[2] = "torino";
    vs[3] = "napoli";
    vs[4] = "fiorentina";
    vs[5] = "como";
    vs[6] = "lazio";
    vs[7] = "roma";
    vs[8] = "bologna";
    vs[9] = "juventus";

    bubble_sort(vs);

    if (!is_sorted(vs)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}