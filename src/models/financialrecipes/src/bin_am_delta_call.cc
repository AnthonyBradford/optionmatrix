#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double option_price_delta_american_call_binomial(const double& S,
						 const double& K,  
						 const double& r,  
						 const double& sigma,
						 const double& t, 
						 const int& no_steps){ // steps in binomial

   double R = exp(r*(t/no_steps));
   double Rinv = 1.0/R;
   double u = exp(sigma*sqrt(t/no_steps));
   double d = 1.0/u;
   double uu= u*u;
   double pUp   = (R-d)/(u-d);
   double pDown = 1.0 - pUp;

   vector<double> prices (no_steps+1);
   prices[0] = S*pow(d, no_steps);
   for (int i=1; i<=no_steps; ++i) prices[i] = uu*prices[i-1];

   vector<double> call_values (no_steps+1);
   for (int i=0; i<=no_steps; ++i) call_values[i] = max(0.0, (prices[i]-K));

   for (int CurrStep=no_steps-1 ; CurrStep>=1; --CurrStep) {
      for (int i=0; i<=CurrStep; ++i)   {
	 prices[i] = d*prices[i+1];
	 call_values[i] = (pDown*call_values[i]+pUp*call_values[i+1])*Rinv;
	 call_values[i] = max(call_values[i], prices[i]-K);        // check for exercise
      };
   }; 
   double delta = (call_values[1]-call_values[0])/(S*u-S*d);
   return delta;
};
