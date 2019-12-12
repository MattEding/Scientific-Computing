#include <iostream>
#include <cblas.h>
#include "io.hpp"

// x <- αx

int main(){
    double  x[] = { 1.0, 2.0, 3.0 };
    double coeff = 4.323;
    int one = 1;
    int n = 3;

    cblas_dscal(n, coeff, x, one);
    io::pprint_vec(x, n);
}
