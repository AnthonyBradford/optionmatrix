#include <cmath>
#include "normdist.h"      // define the normal distribution function

double currency_option_price_call_european( const double& S,      // exchange_rate,
					    const double& X,      // exercise,
					    const double& r,      // r_domestic,
					    const double& r_f,    // r_foreign,
					    const double& sigma,  // volatility,
					    const double& time){   // time to maturity
    double sigma_sqr = sigma*sigma;
    double time_sqrt = sqrt(time);
    double d1 = (log(S/X) + (r-r_f+ (0.5*sigma_sqr)) * time)/(sigma*time_sqrt);
    double d2 = d1 - sigma * time_sqrt;
    return S * exp(-r_f*time) * N(d1) - X * exp(-r*time) * N(d2);
};
