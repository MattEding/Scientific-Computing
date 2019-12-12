#include <functional>
#include <vector>
#include <cblas.h>
#include "io.hpp"


template<typename T>
std::vector<T> create_matrix(std::function<T(int)> func, const int rows, const int cols) {
    std::vector<T> matrix;
    matrix.reserve(rows * cols);
    for (int i = 0; i < (rows * cols); ++i) {
        matrix.emplace_back(func(i));
    }
    return matrix;
}


int main() {
    using matrix_t = std::vector<double>;
    int m = 5, k = 5, n = 5;
    double alpha = 1.0, beta = 0.0;

    matrix_t A = create_matrix<double>([](int i){ return i+1; }, m, k);
    matrix_t B = create_matrix<double>([](int i){ return -i-1; }, k, n);
    matrix_t C(m*n);

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, A.data(), k, B.data(), n, beta, C.data(), n);

    io::pprint_mtx(A, k);
    io::pprint_mtx(B, n);
    io::pprint_mtx(C, n);
}