// file bin_am_prop_div_put.cc
// author: Bernt Arne Oedegaard
// binomial option pricing adjusting for dividends.

#include <cmath>
#include <algorithm>
#include <vector>
#include "fin_recipes.h"

double option_price_put_american_proportional_dividends_binomial(const double& S,
								 const double& K,
								 const double& r,
								 const double& sigma, 
								 const double& time, 
								 const int& no_steps,
								 const vector<double>& dividend_times,
								 const vector<double>& dividend_yields) {
    // when one assume a dividend yield, the binomial tree recombines 
    // note that the last dividend date should be before the expiry date
    int no_dividends=dividend_times.size();
    if (no_dividends == 0)               // just take the regular binomial 
	return option_price_put_american_binomial(S,K,r,sigma,time,no_steps);
    double R = exp(r*(time/no_steps));
    double Rinv = 1.0/R;
    double u = exp(sigma*sqrt(time/no_steps));
    double uu= u*u;
    double d = 1.0/u;
    double pUp   = (R-d)/(u-d);
    double pDown = 1.0 - pUp;

    vector<int>  dividend_steps(no_dividends); // when dividends are paid
    for (int i=0; i<no_dividends; ++i) {
	dividend_steps[i] = (int)(dividend_times[i]/time*no_steps);
    };

    vector<double> prices(no_steps+1);
    vector<double> put_prices(no_steps+1);
    prices[0] = S*pow(d, no_steps);
    for (int i=0; i<no_dividends; ++i) { prices[0]*=(1.0-dividend_yields[i]); };
    for (int i=1; i<=no_steps; ++i) prices[i] = uu*prices[i-1]; // terminal tree nodes
    for (int i=0; i<=no_steps; ++i) put_prices[i] = max(0.0, (K-prices[i]));
    for (int step=no_steps-1; step>=0; --step) {
	for (int i=0;i<no_dividends;++i) {   // check whether dividend paid
	    if (step==dividend_steps[i]) { 
		for (int j=0;j<=(step+1);++j) {
		    prices[j]*=(1.0/(1.0-dividend_yields[i])); 
		};
	    };
	};
	for (int i=0; i<=step; ++i)   {
	    prices[i] = d*prices[i+1];
	    put_prices[i] = (pDown*put_prices[i]+pUp*put_prices[i+1])*Rinv;
	    put_prices[i] = max(put_prices[i], K-prices[i]);         // check for exercise
	};
    };
    return put_prices[0];
};
