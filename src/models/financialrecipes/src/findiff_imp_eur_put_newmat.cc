#include "config.h"

#include <cmath>

#ifdef HAVE_NEWMAT_NEWMAT_H
 #include <newmat/newmat.h>   // definitions for newmat matrix library
#endif

#include <vector>   // standard STL vector template
#include <algorithm>
using namespace std;

#ifdef HAVE_NEWMAT_NEWMAT_H

using namespace NEWMAT;

double option_price_put_european_finite_diff_implicit(const double& S, 
						      const double& K, 
						      const double& r,
						      const double& sigma,
						      const double& time, 
						      const int& no_S_steps, 
						      const int& no_t_steps) {
    double sigma_sqr = sigma*sigma;
    int M=no_S_steps + (no_S_steps%2); // need no_S_steps to be even:
    //    int M=no_S_steps; if ((no_S_steps%2)==1) { ++M; }; // need no_S_steps to be even:
    double delta_S = 2.0*S/M;
    vector<double> S_values(M+1);
    for (int m=0;m<=M;m++) { S_values[m] = m*delta_S; };
    int N=no_t_steps;
    double delta_t = time/N;
    
    BandMatrix A(M+1,1,1); A=0.0;
    A.element(0,0) = 1.0;
    for (int j=1;j<M;++j) {
	A.element(j,j-1) = 0.5*j*delta_t*(r-sigma_sqr*j);    // a[j]
	A.element(j,j)   = 1.0 + delta_t*(r+sigma_sqr*j*j);  // b[j];
	A.element(j,j+1) = 0.5*j*delta_t*(-r-sigma_sqr*j);   // c[j];
    };
    A.element(M,M)=1.0;
    ColumnVector B(M+1);
    for (int m=0;m<=M;++m){ B.element(m) = max(0.0,K-S_values[m]); };
    ColumnVector F=A.i()*B;
    for(int t=N-1;t>0;--t) {
	B = F;
	F = A.i()*B;
    };
    return F.element(M/2);
};

#endif
