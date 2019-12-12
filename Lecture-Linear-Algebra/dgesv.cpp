#include <iostream>
#include <lapacke.h>
#include "io.hpp"

const int N=3, NRHS=2, LDA=N, LDB=N;

int main(){
    int ipiv[N], info;
    double A[N*LDA] = {
        6.80, -2.11, 5.66,
        -6.05, -3.30, 5.36,
        -0.45, 2.58, -2.70
    };
    double B[NRHS*LDB] = {
        4.02, 6.19, -8.22,
        -1.56, 4.00, -8.67
    };
    info = LAPACKE_dgesv(LAPACK_COL_MAJOR, N, NRHS,
    A, LDA, ipiv, B, LDB);

    io::pprint_mtx(A, N, LDA);
    io::pprint_mtx(B, NRHS, LDB);
    io::pprint_vec(ipiv, N);
    std::cout << info << std::endl;
}
