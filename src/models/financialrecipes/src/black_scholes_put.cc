#include <cmath>              // mathematical library
#include "normdist.h"          // this defines the normal distribution
using namespace std; 

double option_price_put_black_scholes(const double& S,      // spot price
				      const double& K,      // Strike (exercise) price,
				      const double& r,      // interest rate
				      const double& sigma,  // volatility
				      const double& time){
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt;
    double d2 = d1-(sigma*time_sqrt);
    return K*exp(-r*time)*N(-d2) - S*N(-d1);
};
