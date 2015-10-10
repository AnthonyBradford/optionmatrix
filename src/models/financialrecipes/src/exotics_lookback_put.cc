#include <cmath>
using namespace std;
#include "normdist.h"

double option_price_european_lookback_put(const double& S,
					   const double& Smax,
					   const double& r,
					   const double& q,
					   const double& sigma,
					   const double& time){
    if (r==q) return 0;
    double sigma_sqr=sigma*sigma;
    double time_sqrt = sqrt(time);
    double b1 = (log(S/Smax) + (-r+q+sigma_sqr/2.0)*time)/(sigma*time_sqrt);
    double b2 = b1-sigma*time_sqrt;
    double b3 = (log(S/Smax) + (r-q-sigma_sqr/2.0)*time)/(sigma*time_sqrt);
    double Y2 = (2.0 * (r-q-sigma_sqr/2.0)*log(Smax/S))/sigma_sqr;
    double p =
	Smax * exp(-r*time)*(N(b1)-(sigma_sqr/(2*(r-q)))*exp(Y2)*N(-b3))
	+ S * exp(-q*time)*(sigma_sqr/(2.0*(r-q)))*N(-b2)
	- S * exp(-q*time)*N(b2);
    return p;
};
