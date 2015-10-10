#include "config.h"

#include <cmath>

using namespace std;

#ifdef HAVE_ITPP_ITBASE_H
 #include <itpp/itbase.h>
 using namespace itpp;
#endif

#ifdef HAVE_ITPP_ITBASE_H

double option_price_put_american_finite_diff_implicit_itpp(const double& S,
							   const double& K, 
							   const double& r,
							   const double& sigma,
							   const double& time, 
							   const int& no_S_steps,
							   const int& no_t_steps) {
    double sigma_sqr = sigma*sigma;
    int M=no_S_steps + (no_S_steps%2); // need no_S_steps to be even:

    double delta_S = 2.0*S/double(M);
    double S_values[M+1];
    for (int m=0;m<=M;m++) { S_values[m] = m*delta_S; };
    int N=no_t_steps;
    double delta_t = time/N;
    
    mat A = zeros(M+1,M+1);
    A(0,0) = 1.0;
    for (int j=1;j<M;++j) {
	A(j,j-1) = 0.5*j*delta_t*(r-sigma_sqr*j);    // a[j]
	A(j,j)   = 1.0 + delta_t*(r+sigma_sqr*j*j);  // b[j];
	A(j,j+1) = 0.5*j*delta_t*(-r-sigma_sqr*j);   // c[j];
    };
    A(M,M)=1.0;
    vec B(M+1);
    for (int m=0;m<=M;++m){ B(m) = max(0.0,K-S_values[m]); };
    mat InvA = inv(A);
    vec F=InvA*B;
    for(int t=N-1;t>0;--t) {
	B = F;
	F = InvA*B;
	for (int m=1;m<M;++m) { 	// now check for exercise
	    F(m) = max(F(m), K-S_values[m]);
	};
    };
    return F(M/2);
};

#endif
