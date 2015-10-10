#include <cmath>             // standard mathematical library
#include <algorithm>             // defining the max() operator
#include <vector>           // STL vector templates
using namespace std;

double option_price_call_european_binomial( const double& S,     // spot price
					    const double& K,     // exercice price
					    const double& r,     // interest rate
					    const double& sigma, // volatility
					    const double& t,     // time to maturity
					    const int& steps){  // no steps in binomial tree
   double R = exp(r*(t/steps));            // interest rate for each step
   double Rinv = 1.0/R;                    // inverse of interest rate
   double u = exp(sigma*sqrt(t/steps));    // up movement
   double uu = u*u;
   double d = 1.0/u;
   double p_up = (R-d)/(u-d);
   double p_down = 1.0-p_up;
   vector<double> prices(steps+1);       // price of underlying
   prices[0] = S*pow(d, steps);  // fill in the endnodes.
   for (int i=1; i<=steps; ++i) prices[i] = uu*prices[i-1];
   vector<double> call_values(steps+1);       // value of corresponding call 
   for (int i=0; i<=steps; ++i) call_values[i] = max(0.0, (prices[i]-K)); // call payoffs at maturity
   for (int step=steps-1; step>=0; --step) {
      for (int i=0; i<=step; ++i) {
	 call_values[i] = (p_up*call_values[i+1]+p_down*call_values[i])*Rinv;
      };
   };
   return call_values[0];
};
