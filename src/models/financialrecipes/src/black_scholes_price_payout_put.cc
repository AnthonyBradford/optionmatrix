// file: black_scholes_price_
// author: Bernt A Oedegaard
//    Calculation of the Black Scholes option price formula, 
//    special case where the underlying is paying out a yield of b.

#include <math.h>              // mathematical library
#include "normdist.h"          // this defines the normal distribution
 
double option_price_european_put_payout( const double& S, // spot price
					 const double& K, // Strike (exercise) price,
					 const double& r,  // interest rate
					 const double& q,  // yield on underlying
					 const double& sigma,
					 const double& time) {  
    double sigma_sqr = pow(sigma,2);
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K) + (r-q + 0.5*sigma_sqr)*time)/(sigma*time_sqrt);
    double d2 = d1-(sigma*time_sqrt);
    double put_price = K * exp(-r*time)*N(-d2)-S*exp(-q*time)*N(-d1);
    return put_price;
};
