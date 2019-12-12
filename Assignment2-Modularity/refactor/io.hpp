#include <iostream>
#include <fstream>
#include <string>


#ifndef IO_NAMESPACE
#define IO_NAMESPACE io
#endif

namespace IO_NAMESPACE
{
/*======================== LOAD ========================*/
template<typename T>
void load(std::ifstream& infile, T& arg) {
    infile >> arg;
}

template<typename T, typename... Ts>
void load(std::ifstream& infile, T& arg, Ts&... args) {
    load(infile, arg);
    load(infile, args...);
}

/*======================== SAVE ========================*/
template<typename T>
void save(std::ofstream& outfile, const std::string& msg, const T& arg) {
    outfile << msg << arg << '\n';
}

template<typename T, typename... Ts>
void save(std::ofstream& outfile, const std::string& msg, const T& arg, const Ts&... args) {
    save(outfile, msg, arg);
    save(outfile, args...);
}

/*======================== PRINT ========================*/
template<typename T>
void print(const T& arg) {
    std::cout << arg << '\n';
}

template<typename T, typename... Ts>
void print(const T& arg, const Ts&... args) {
    print(arg);
    print(args...);
}
}