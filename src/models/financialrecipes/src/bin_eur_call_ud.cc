#include <cmath>            // standard mathematical library
#include <algorithm>        // defining the max() operator
#include <vector>           // STL vector templates
using namespace std;

double option_price_call_european_binomial_multi_period_given_ud(const double& S,     // spot price
								 const double& K,     // exercice price
								 const double& r,    // interest rate (per period)
								 const double& u,   // up movement
								 const double& d,   // down movement
								 const int& no_periods){  // no steps in binomial tree
   double Rinv = exp(-r);                    // inverse of interest rate
   double uu = u*u;
   double p_up = (exp(r)-d)/(u-d);
   double p_down = 1.0-p_up;
   vector<double> prices(no_periods+1);       // price of underlying
   prices[0] = S*pow(d, no_periods);  // fill in the endnodes.
   for (int i=1; i<=no_periods; ++i) prices[i] = uu*prices[i-1];
   vector<double> call_values(no_periods+1);       // value of corresponding call 
   for (int i=0; i<=no_periods; ++i) call_values[i] = max(0.0, (prices[i]-K)); // call payoffs at maturity
   for (int step=no_periods-1; step>=0; --step) {
      for (int i=0; i<=step; ++i) {
	 call_values[i] = (p_up*call_values[i+1]+p_down*call_values[i])*Rinv;
      };
   };
   return call_values[0];
};
