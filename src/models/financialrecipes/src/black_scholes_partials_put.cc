#include <cmath>
#include "normdist.h"               

void option_price_partials_put_black_scholes(const double& S, // spot price
					     const double& K, // Strike (exercise) price,
					     const double& r,  // interest rate
					     const double& sigma,
					     const double& time,
					     double& Delta, //  partial wrt S
					     double& Gamma, //  second prt wrt S
					     double& Theta,  // partial wrt time
					     double& Vega,  //  partial wrt sigma
					     double& Rho){    // partial wrt r
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt; 
    double d2 = d1-(sigma*time_sqrt);
    Delta = -N(-d1);
    Gamma = n(d1)/(S*sigma*time_sqrt);
    Theta = -(S*sigma*n(d1)) / (2*time_sqrt)+ r*K * exp(-r*time) * N(-d2); 
    Vega  = S * time_sqrt * n(d1);
    Rho   = -K*time*exp(-r*time) * N(-d2);
};
