#include <cmath>
#include "normdist.h"

double bond_option_price_call_zero_black_scholes(const double& B, 
						 const double& X, 
						 const double& r, 
						 const double& sigma,
						 const double& time){  
    double time_sqrt = sqrt(time);
    double d1 = (log(B/X)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double d2 = d1-(sigma*time_sqrt);
    double c = B * N(d1) - X * exp(-r*time) * N(d2);
    return c;
};
