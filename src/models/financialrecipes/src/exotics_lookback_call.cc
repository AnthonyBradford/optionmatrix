#include <cmath>
using namespace std;
#include "normdist.h"

double option_price_european_lookback_call(const double& S,
					   const double& Smin,
					   const double& r,
					   const double& q,
					   const double& sigma,
					   const double& time){
    if (r==q) return 0;
    double sigma_sqr=sigma*sigma;
    double time_sqrt = sqrt(time);
    double a1 = (log(S/Smin) + (r-q+sigma_sqr/2.0)*time)/(sigma*time_sqrt);
    double a2 = a1-sigma*time_sqrt;
    double a3 = (log(S/Smin) + (-r+q+sigma_sqr/2.0)*time)/(sigma*time_sqrt);
    double Y1 = 2.0 * (r-q-sigma_sqr/2.0)*log(S/Smin)/sigma_sqr;
    return S * exp(-q*time)*N(a1)- S*exp(-q*time)*(sigma_sqr/(2.0*(r-q)))*N(-a1)
	- Smin * exp(-r*time)*(N(a2)-(sigma_sqr/(2*(r-q)))*exp(Y1)*N(-a3));
};
