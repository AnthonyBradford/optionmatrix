// file bin_am_div_put.cc
// author: Bernt Arne Oedegaard
// binomial option pricing adjusting for dividends.

#include <cmath>
#include <vector>
#include "fin_recipes.h"

double option_price_put_american_discrete_dividends_binomial( const double& S, 
							      const double& K,
							      const double& r,
							      const double& sigma, 
							      const double& t, 
							      const int& steps,
							      const vector<double>& dividend_times,
							      const vector<double>& dividend_amounts) 
// given an amount of dividend, the binomial tree does not recombine, have to 
// start a new tree at each ex-dividend date.
// do this recursively, at each ex dividend date, at each step, put the 
// binomial formula starting at that point to calculate the value of the live
// option, and compare that to the value of exercising now.
{
   int no_dividends = dividend_times.size();
   if (no_dividends == 0)               // just take the regular binomial 
      return option_price_put_american_binomial(S,K,r,sigma,t,steps);
   int steps_before_dividend = (int)(dividend_times[0]/t*steps);
    
   const double R = exp(r*(t/steps));
   const double Rinv = 1.0/R;
   const double u = exp(sigma*sqrt(t/steps));
   const double uu= u*u;
   const double d = 1.0/u;
   double pUp   = (R-d)/(u-d);
   double pDown = 1.0 - pUp;
   double dividend_amount = dividend_amounts[0];
   vector<double> tmp_dividend_times(no_dividends-1);  // temporaries with 
   vector<double> tmp_dividend_amounts(no_dividends-1);  // one less dividend
   for (int i=0;i<no_dividends-1;++i){ 
      tmp_dividend_amounts[i] = dividend_amounts[i+1];
      tmp_dividend_times[i]   = dividend_times[i+1] - dividend_times[0];
   };
   vector<double> prices(steps_before_dividend+1);
   vector<double> put_values(steps_before_dividend+1);

   prices[0] = S*pow(d, steps_before_dividend);
   for (int i=1; i<=steps_before_dividend; ++i) prices[i] = uu*prices[i-1];
   for (int i=0; i<=steps_before_dividend; ++i){
      double value_alive 
	 = option_price_put_american_discrete_dividends_binomial(
	    prices[i]-dividend_amount, K, r, sigma, 
	    t-dividend_times[0],               // time after first dividend
	    steps-steps_before_dividend, 
	    tmp_dividend_times, tmp_dividend_amounts);  
      // what is the value of keeping the option alive?  Found recursively, 
      // with one less dividend, the stock price is current value 
      // less the dividend.
      put_values[i] = max(value_alive,(K-prices[i]));  // compare to exercising now
   };
   for (int step=steps_before_dividend-1; step>=0; --step) {
      for (int i=0; i<=step; ++i)   {
	 prices[i] = d*prices[i+1];
	 put_values[i] = (pDown*put_values[i]+pUp*put_values[i+1])*Rinv;
	 put_values[i] = max(put_values[i], K-prices[i]);         // check for exercise
      };
   };
   return put_values[0];
};
