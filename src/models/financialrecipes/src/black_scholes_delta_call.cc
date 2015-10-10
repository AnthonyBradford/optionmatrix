#include <cmath>
#include "normdist.h"               

double option_price_delta_call_black_scholes(const double& S,     // spot price
					     const double& K,     // Strike (exercise) price,
					     const double& r,     // interest rate
					     const double& sigma, // volatility
					     const double& time){  // time to maturity
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double delta = N(d1);
    return delta;
};
