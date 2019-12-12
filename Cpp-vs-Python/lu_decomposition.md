# Solve with LU Decomposion
## Python
```python
>>> import numpy as np
>>> from scipy import linalg

>>> A = np.array([[2, -1], [-1, 3]])
>>> b = np.array([[1, 2], [3, 1]])

>>> linalg.lu_solve(linalg.lu_factor(A), b)
array([[1.2, 1.4],
       [1.4, 0.8]])

>>> linalg.eigvals(A)                                                                                    array([1.38196601+0.j, 3.61803399+0.j])
```

## C++
```cpp
#include <iostream>
#include <Eigen/Dense>

int main() {
    Eigen::Matrix<float, 2, 2> A, b, x;
    A << 2, -1, -1, 3;
    b << 1, 2, 3, 1;

    x = A.lu().solve(b);
    std::cout << x << endl;
    // 1.2 1.4
    // 1.4 0.8

    std::cout << A.eigenvalues() << endl;
    // (1.38917,0)
    // (3.61803,0)
}
```