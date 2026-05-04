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
                std::swap(A[j], A[j-1]);
           }
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
            std::swap(A[i], A[min]);
    }
}

template<typename T>
void insertion_sort(std::vector<T>& A){      //non c'è const perchè modifico A
    int n = A.size();
    for (int j = 1; j < n; j++) {
        T key = std::move(A[j]);
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = std::move(A[i]);
            i--;
        }
        A[i + 1] = std::move(key);
    }
}

template<typename T>
void merge(std::vector<T>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = std::move(A[p + i]);
    for (int j = 0; j < n2; j++) R[j] = std::move(A[q + 1 + j]);

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) A[k++] = std::move(L[i++]);
        else A[k++] = std::move(R[j++]);
    }
    while (i < n1) A[k++] = std::move(L[i++]);
    while (j < n2) A[k++] = std::move(R[j++]);
}

template<typename T>
void merge_sort(std::vector<T>& A, int p, int r) {

    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

template<typename T>
int partition(std::vector<T>& A, int p, int r) {
    T x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

template<typename T>
void quick_sort(std::vector<T>& A, int p, int r) {
   
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

template<typename T>
void hybrid_quick_sort(std::vector<T>& A, int p, int r) {
   
    const int SOGLIA = 64; 
    
    if (r - p + 1 <= SOGLIA) {

        for (int j = p + 1; j <= r; j++) {
            T key = std::move(A[j]);
            int i = j - 1;
            while (i >= p && A[i] > key) {
                A[i + 1] = std::move(A[i]);
                i--;
            }
            A[i + 1] = std::move(key);
        }
    } else if (p < r) {
        int q = partition(A, p, r);
        hybrid_quick_sort(A, p, q - 1);
        hybrid_quick_sort(A, q + 1, r);
    }
}