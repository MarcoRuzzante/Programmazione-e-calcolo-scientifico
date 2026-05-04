#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "sorts.h"
#include "randfiller.h"
#include "timecounter.h"

int main(void){
    randfiller rf;
    timecounter tc;
    
    int N = 100;

    std::cout << "Dim\tBubble\t\tInsertion\tSelection\tMerge\t\tQuick\t\tHybrid\t\tStd\n";

    for (int dim = 4; dim <= 8192; dim *= 2) {
        
        std::vector<std::vector<double>> orig(N, std::vector<double>(dim));
        for (int i = 0; i < N; i++) {
            rf.fill(orig[i], -100.0, 100.0);
        }

        auto vb = orig;
        auto vi = orig;
        auto vs = orig;
        auto vm = orig;
        auto vq = orig;
        auto vh = orig;
        auto vstd = orig;

        tc.tic();
        for (int i = 0; i < N; i++) bubble_sort(vb[i]);
        double time_bubble = tc.toc() / N;

        tc.tic();
        for (int i = 0; i < N; i++) insertion_sort(vi[i]);
        double time_insertion = tc.toc() / N;

        tc.tic();
        for (int i = 0; i < N; i++) selection_sort(vs[i]);
        double time_selection = tc.toc() / N;

        tc.tic();
        for (int i = 0; i < N; i++) merge_sort(vm[i],0,dim-1);
        double time_merge = tc.toc() / N;

        tc.tic();
        for (int i = 0; i < N; i++) quick_sort(vq[i],0,dim-1);
        double time_quick = tc.toc() / N;

        tc.tic();
        for (int i = 0; i < N; i++) hybrid_quick_sort(vh[i],0,dim-1);
        double time_hybrid = tc.toc() / N;

        tc.tic();
        for (int i = 0; i < N; i++) std::sort(vstd[i].begin(), vstd[i].end());
        double time_std = tc.toc() / N;

        std::cout << dim << "\t" << time_bubble << "\t" << time_insertion << "\t"<< time_selection << "\t" << time_merge << "\t" << time_quick << "\t" << time_hybrid << "\t" << time_std << "\n";
    }

    return EXIT_SUCCESS;
}