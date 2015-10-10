#include <cmath>     // c library of math functions
using namespace std; // which is part of the standard namespace

// most C compilers define PI, but just in case it doesn't 
#ifndef PI 
#define PI 3.141592653589793238462643
#endif

double n(const double& z) {  // normal distribution function    
    return (1.0/sqrt(2.0*PI))*exp(-0.5*z*z);
};
