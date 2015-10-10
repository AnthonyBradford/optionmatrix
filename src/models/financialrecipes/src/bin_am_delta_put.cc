
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double option_price_delta_american_put_binomial(const double& S,  // spot price 
						const double& K,  // Exercise price,
						const double& r,     // interest rate
						const double& sigma, // volatility
						const double& t,  // time to maturity
						const int& no_steps){ // steps in binomial
   vector<double> prices (no_steps+1);
   vector<double> put_values  (no_steps+1);
   double R = exp(r*(t/no_steps));
   double Rinv = 1.0/R;
   double u = exp(sigma*sqrt(t/no_steps));
   double d = 1.0/u;
   double uu= u*u;
   double pUp   = (R-d)/(u-d);
   double pDown = 1.0 - pUp;
   prices[0] = S*pow(d, no_steps);
   int i;
   for (i=1; i<=no_steps; ++i) prices[i] = uu*prices[i-1];
   for (i=0; i<=no_steps; ++i) put_values[i] = max(0.0, (K - prices[i]));
   for (int CurrStep=no_steps-1 ; CurrStep>=1; --CurrStep) {
      for (i=0; i<=CurrStep; ++i)   {
	 prices[i] = d*prices[i+1];
	 put_values[i] = (pDown*put_values[i]+pUp*put_values[i+1])*Rinv;
	 put_values[i] = max(put_values[i], K-prices[i]);        // check for exercise
      };
   }; 
   double delta = (put_values[1]-put_values[0])/(S*u-S*d);
   return delta;
};
