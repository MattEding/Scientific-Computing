#pragma once

#include <iostream>


namespace io
{
// MATRICES
template<typename T>
void pprint_mtx(T *matrix, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < (rows * cols); ++i) {
        if (i % rows == 0) {
            std::cout << '\n';
        }
        std::cout << matrix[i] << '\t';
    }
    std::cout << std::endl;
}

template<typename C>
void pprint_mtx(const C &matrix, const size_t lead_dim) {
    pprint_mtx(matrix.data(), matrix.size() / lead_dim, lead_dim);
}

// VECTORS
template<typename T>
void pprint_vec(T *vector, const size_t len) {
    std::cout << '\n';
    for (size_t i = 0; i < len; ++i) {
        std::cout << vector[i] << '\t';
    }
    std::cout << '\n' << std::endl;
}

template<typename C>
void pprint_vec(const C &matrix) {
    pprint_vec(matrix.data(), matrix.size());
}
}
