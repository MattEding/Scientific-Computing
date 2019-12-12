#include <fstream>
#include <memory>
#include <string>
#include "io.hpp"


int main(int argc, char* argv[]) {
    // Physical parameters
    double  c       =   1.0;  // wave speed
    double  tau     =  20.0;  // damping time
    double  x1      = -26.0;  // left most x value
    double  x2      = +26.0;  // right most x value

    // Simulation parameters
    double  runtime = 200.0;  // how long should the simulation try to compute?
    double  dx      = 0.02;   // spatial grid size

    // Output parameters
    double  outtime =  1.0;   // how often should a snapshot of the wave be written out?
    std::string outfilename = "result.txt"; // name of the file with the output data

    // Read the values from a file if specified on the command line
    if (argc > 1) {
        std::ifstream infile(argv[1]);
        io::load(infile, c, tau, x1, x2, runtime, dx, outtime, outfilename);
        infile.close();
    }

    // Derived parameters
    int     ngrid   = (x2-x1)/dx;  // number of x points
    int     npnts   = ngrid + 2;   // number of x points including boundary points
    double  dt      = 0.5*dx/c;    // time step size
    int     nsteps  = runtime/dt;  // number of steps of that size to reach runtime
    int     nper    = outtime/dt;  // how many step s between snapshots

    // Define and allocate arrays
    double* rho_prev = new double[npnts]; // time step t-1
    double* rho      = new double[npnts]; // time step t
    double* rho_next = new double[npnts]; // time step t+1
    double* x        = new double[npnts]; // x values


    // Open output file
    std::ofstream outfile(outfilename);
    io::save(outfile,
        "#c       ", c      ,
        "#tau     ", tau    ,
        "#x1      ", x1     ,
        "#x2      ", x2     ,
        "#runtime ", runtime,
        "#dx      ", dx     ,
        "#outtime ", outtime,
        "#ngrid   ", ngrid  ,
        "#dt      ", dt     ,
        "#nsteps  ", nsteps ,
        "#nper    ", nper
    );
    outfile.close();

    io::print(c, tau, x1, x2, runtime, dx, outtime, outfilename);
}