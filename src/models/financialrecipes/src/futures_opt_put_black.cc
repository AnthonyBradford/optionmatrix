#include <cmath>                                 // mathematics library
#include "normdist.h"                             // normal distribution
using namespace std;

double futures_option_price_put_european_black(const double& F,     // futures price
					       const double& X,     // exercise price
					       const double& r,     // interest rate
					       const double& sigma, // volatility
					       const double& time){ // time to maturity
    double sigma_sqr = sigma*sigma;
    double time_sqrt = sqrt(time);
    double d1 = (log (F/X) + 0.5 * sigma_sqr * time) / (sigma * time_sqrt);
    double d2 = d1 - sigma * time_sqrt;
    return  exp(-r*time)*(X * N(-d2) - F * N(-d1));
};
