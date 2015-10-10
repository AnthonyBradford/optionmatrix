#include <cmath>             // standard mathematical library
#include <algorithm>             // defining the max() operator
using namespace std;

double option_price_call_european_binomial_single_period( const double& S,     // spot price
							  const double& X,     // exercice price
							  const double& r,     // interest rate (per period)
							  const double& u,     // up movement
							  const double& d){   // down movement
   double p_up = (exp(r)-d)/(u-d);
   double p_down = 1.0-p_up;
   double c_u = max(0.0,(u*S-X));
   double c_d = max(0.0,(d*S-X));
   double call_price = exp(-r)*(p_up*c_u+p_down*c_d);
   return call_price;
};
