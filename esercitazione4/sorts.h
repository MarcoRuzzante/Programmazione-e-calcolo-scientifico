#pragma once

#include <vector>
#include <algorithm>

template<typename T>
bool is_sorted(const std::vector<T>& vec){
    int n = vec.size();
    for (int i = 1; i < n; i++) {
        if (vec[i] < vec[i - 1]) {
            return false;
        }
    }
    return true;
}

template<typename T>
void bubble_sort(std::vector<T>& A){        //non c'è const perchè modifico A

    int n = A.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                T tmp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = tmp;            }
        }
    }
}

template<typename T>
void selection_sort(std::vector<T>& A){     //non c'è const perchè modifico A

    int n = A.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        T tmp = A[i];
        A[i] = A[min];
        A[min] = tmp;
    }
}

template<typename T>
void insertion_sort(std::vector<T>& A){      //non c'è const perchè modifico A
    int n = A.size();
    for (int j = 1; j < n; j++) {
        T key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
}