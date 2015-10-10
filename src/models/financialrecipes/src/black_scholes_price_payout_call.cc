#include <cmath>              // mathematical library
#include "normdist.h"          // this defines the normal distribution
using namespace std;

double option_price_european_call_payout( const double& S, // spot price
					  const double& X, // Strike (exercise) price,
					  const double& r,  // interest rate
					  const double& q,  // yield on underlying
					  const double& sigma, // volatility
					  const double& time) { // time to maturity
    double sigma_sqr = pow(sigma,2);
    double time_sqrt = sqrt(time);
    double d1 = (log(S/X) + (r-q + 0.5*sigma_sqr)*time)/(sigma*time_sqrt);
    double d2 = d1-(sigma*time_sqrt);
    double call_price = S * exp(-q*time)* N(d1) - X * exp(-r*time) * N(d2);
    return call_price;
};
