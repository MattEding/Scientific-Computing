//
// wave1d.cc - Simulates a one-dimensional damped wave equation
//
// Ramses van Zon - January 2015/2017
//

#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char* argv[])
{
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
        infile >> c;
        infile >> tau;
        infile >> x1;
        infile >> x2;
        infile >> runtime;
        infile >> dx;
        infile >> outtime;
        infile >> outfilename;
        infile.close();
    }

    // Derived parameters
    int     ngrid   = (x2-x1)/dx;  // number of x points
    int     npnts   = ngrid + 2;   // number of x points including boundary points
    double  dt      = 0.5*dx/c;    // time step size
    int     nsteps  = runtime/dt;  // number of steps of that size to reach runtime
    int     nper    = outtime/dt;  // how many step s between snapshots

    // Open output file
    std::ofstream fout(outfilename);

    // Report all the values
    fout << "#c       " << c       << std::endl;
    fout << "#tau     " << tau     << std::endl;
    fout << "#x1      " << x1      << std::endl;
    fout << "#x2      " << x2      << std::endl;
    fout << "#runtime " << runtime << std::endl;
    fout << "#dx      " << dx      << std::endl;
    fout << "#outtime " << outtime << std::endl;
    fout << "#ngrid   " << ngrid   << std::endl;
    fout << "#dt      " << dt      << std::endl;
    fout << "#nsteps  " << nsteps  << std::endl;
    fout << "#nper    " << nper    << std::endl;

    // Define and allocate arrays
    double* rho_prev = new double[npnts]; // time step t-1
    double* rho      = new double[npnts]; // time step t
    double* rho_next = new double[npnts]; // time step t+1
    double* x        = new double[npnts]; // x values

    // Initialize
    for (int i = 0; i < npnts; i++) {
        x[i] = x1 + ((i-1)*(x2-x1))/ngrid;
        rho[i] = 0.0;
        rho_prev[i] = 0.0;
        rho_next[i] = 0.0;
    }

    // Excite
    double x14 = 0.25*(x2-x1) + x1;
    double x12 = 0.5*(x2+x1);
    double x34 = 0.75*(x2-x1) + x1;
    for (int i = npnts/4 + 1; i < 3*npnts/4; i++) {
        if (x[i]<x14 || x[i]>x34)
            rho[i] = 0.0;
        else
            rho[i] = 0.25 - fabs(x[i]-x12)/(x2-x1);
        rho_prev[i] = rho[i];
    }

    // Output initial signal
    fout << "\n#t = " << 0 << "\n";
    for (int i = 1; i <= ngrid; i++)
        fout << x[i] << " " << rho[i] << "\n";

    // Take timesteps
    for (int s = 0; s < nsteps; s++) {

        // Set zero dirichlet boundary conditions
        rho[0] = 0.0;
        rho[ngrid+1] = 0.0;

        // Evolve
        for (int i = 1; i <= ngrid; i++) {
            double laplacian = pow(c/dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]);
            double friction = (rho[i] - rho_prev[i])/tau;
            rho_next[i] = 2*rho[i] - rho_prev[i] + dt*(laplacian*dt-friction);
        }

        // Rotate array pointers so t+1 becomes the new t etc.
	for (int i = 1; i <= ngrid; i++) {
            double temp = rho_prev[i];
        	rho_prev[i] = rho[i];
	        rho[i]      = rho_next[i];
        	rho_next[i] = temp;
	}

        // Output density
        if ((s+1)%nper == 0) {
            fout << "\n\n# t = " << s*dt << "\n";
            for (int i = 1; i <= ngrid; i++)
                fout << x[i] << " " << rho[i] << "\n";
        }
    }

    // Close file
    fout.close();
    std::cout << "Results written to "<< outfilename << std::endl;

    // Deallocate memory
    delete[] rho_prev;
    delete[] rho;
    delete[] rho_next;
    delete[] x;

    return 0;
}
