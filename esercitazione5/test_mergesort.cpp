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
        merge_sort(v,0,v.size()-1);
        if (!is_sorted(v)) {
            return EXIT_FAILURE;
        }
    }

    std::vector<std::string> vs = {"inter", "milan", "torino", "napoli", "fiorentina", "como", "lazio", "roma", "bologna", "juventus"};
    merge_sort(vs,0,vs.size()-1);
    if (!is_sorted(vs)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}