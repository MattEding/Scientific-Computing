#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <Eigen/Dense>


auto load_matrix(const std::string &filename, const size_t rows, const size_t cols,
                 const std::string &ignore = ",{}") {
    std::ifstream infile(filename);
    std::stringstream stream;
    char c;
    while (infile >> c) {
        if (ignore.find(c) == std::string::npos) {
            stream << c;
        }
        else {
            stream << ' ';
        }
    }
    infile.close();

    double n;
    Eigen::MatrixXd mtx(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j){
            stream >> n;
            mtx(i, j) = n;
        }
    }
    return mtx;
}


int main() {
    const std::string filename = "matrix.txt";
    const size_t r = 10, c = 10;
    auto A = load_matrix(filename, r, c);
    std::cout << A << std::endl;
    Eigen::VectorXcd eigvals = A.eigenvalues();
    std::cout << eigvals << std::endl;
}
