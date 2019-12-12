#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>


template<typename Container, typename Function>
Container apply(Container c, Function f) {
    std::for_each(c.begin(), c.end(), f);
    return c;
}


int main() {
    using Real = double;

    Real start = -4, stop = 0, step = 0.25;
    std::size_t size = (stop - start) / step;

    std::vector<Real> ts;
    ts.reserve(size);
    for (Real i = 0; i < size; ++i) {
        ts.emplace_back(i);
    }
    ts = apply(ts, [step, start](auto &t){ t = start+step*t; });

    auto xs = apply(ts, [](auto &t){ t = std::sin(2*t)/(1+t*t); });
    auto ys = apply(ts, [](auto &t){ t = std::cos(3*t)/(1+t*t); });

#define STDOUT
#ifdef STDOUT
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << ts[i] << '\t'
                  << xs[i] << '\t'
                  << ys[i] << '\t' << '\n';
    }
#else
    std::ofstream fout("out.txt");
    for (std::size_t i = 0; i < size; ++i) {
        fout << ts[i] << '\t'
             << xs[i] << '\t'
             << ys[i] << '\t' << '\n';
    }
    fout.close();
#endif
}
