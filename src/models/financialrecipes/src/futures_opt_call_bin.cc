#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double futures_option_price_call_american_binomial(const double& F, // price futures contract
						   const double& K, // exercise price
						   const double& r, // interest rate
						   const double& sigma, // volatility
						   const double& time, // time to maturity
						   const int& no_steps) { // number of steps
   vector<double> futures_prices(no_steps+1);
   vector<double> call_values (no_steps+1);
   double t_delta= time/no_steps;
   double Rinv = exp(-r*(t_delta));
   double u = exp(sigma*sqrt(t_delta));
   double d = 1.0/u;
   double uu= u*u;
   double pUp   = (1-d)/(u-d);   // note how probability is calculated
   double pDown = 1.0 - pUp;
   futures_prices[0] = F*pow(d, no_steps);
   int i;
   for (i=1; i<=no_steps; ++i) futures_prices[i] = uu*futures_prices[i-1]; // terminal tree nodes
   for (i=0; i<=no_steps; ++i) call_values[i] = max(0.0, (futures_prices[i]-K));
   for (int step=no_steps-1; step>=0; --step) {
      for (i=0; i<=step; ++i)   {
	 futures_prices[i] = d*futures_prices[i+1];
	 call_values[i] = (pDown*call_values[i]+pUp*call_values[i+1])*Rinv;
	 call_values[i] = max(call_values[i], futures_prices[i]-K); // check for exercise
      };
   };
   return call_values[0];
};
