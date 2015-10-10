#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double option_price_put_american_finite_diff_explicit( const double&  S, 
						       const double&  K, 
						       const double&  r,
						       const double&  sigma,
						       const double&  time,
						       const int& no_S_steps,
						       const int& no_t_steps) {
    double sigma_sqr = sigma*sigma;
    int M=no_S_steps+(no_S_steps%2); // need no_S_steps to be even:
    double delta_S = 2.0*S/M;
    vector<double> S_values(M+1);
    for (int m=0;m<=M;m++) { S_values[m] = m*delta_S; };
    int N=no_t_steps;
    double delta_t = time/N;
    
    vector<double> a(M);
    vector<double> b(M);
    vector<double> c(M);
    double r1=1.0/(1.0+r*delta_t);
    double r2=delta_t/(1.0+r*delta_t);
    for (int j=1;j<M;j++){
	a[j] = r2*0.5*j*(-r+sigma_sqr*j);
	b[j] = r1*(1.0-sigma_sqr*j*j*delta_t);
	c[j] = r2*0.5*j*(r+sigma_sqr*j);
    };
    vector<double> f_next(M+1);
    for (int m=0;m<=M;++m) { f_next[m]=max(0.0,K-S_values[m]); };
    vector<double> f(M+1);
    for (int t=N-1;t>=0;--t) {
	f[0]=K;
	for (int m=1;m<M;++m) {
	    f[m]=a[m]*f_next[m-1]+b[m]*f_next[m]+c[m]*f_next[m+1];
	    f[m] = max(f[m],K-S_values[m]);  // check for exercise
	};
	f[M] = 0;
	for (int m=0;m<=M;++m) { f_next[m] = f[m]; };
    };
    return f[M/2];
};
