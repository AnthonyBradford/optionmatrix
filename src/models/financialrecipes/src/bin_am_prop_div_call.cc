#include <cmath>
#include <algorithm>
#include <vector>
#include "fin_recipes.h"
#include <iostream>

double option_price_call_american_proportional_dividends_binomial(const double& S, 
								  const double& K,
								  const double& r,
								  const double& sigma, 
								  const double& time, 
								  const int& no_steps,
								  const vector<double>& dividend_times,
								  const vector<double>& dividend_yields) {
    // note that the last dividend date should be before the expiry date, problems if dividend at terminal node
    int no_dividends=dividend_times.size();
    if (no_dividends == 0) {
	return option_price_call_american_binomial(S,K,r,sigma,time,no_steps); // price w/o dividends
    };
    double delta_t = time/no_steps;
    double R = exp(r*delta_t);
    double Rinv = 1.0/R;
    double u = exp(sigma*sqrt(delta_t));
    double uu= u*u;
    double d = 1.0/u;
    double pUp   = (R-d)/(u-d);
    double pDown = 1.0 - pUp;
    vector<int> dividend_steps(no_dividends); // when dividends are paid
    for (int i=0; i<no_dividends; ++i) {
	dividend_steps[i] = (int)(dividend_times[i]/time*no_steps);
    };
    vector<double> prices(no_steps+1);
    vector<double> call_prices(no_steps+1);
    prices[0] = S*pow(d, no_steps); // adjust downward terminal prices by dividends
    for (int i=0; i<no_dividends; ++i) { prices[0]*=(1.0-dividend_yields[i]); };
    for (int i=1; i<=no_steps; ++i)  { 	prices[i] = uu*prices[i-1]; }; 
    for (int i=0; i<=no_steps; ++i) call_prices[i] = max(0.0, (prices[i]-K));

    for (int step=no_steps-1; step>=0; --step) {
	for (int i=0;i<no_dividends;++i) {   // check whether dividend paid
	    if (step==dividend_steps[i]) { 
		for (int j=0;j<=(step+1);++j) {
		    prices[j]*=(1.0/(1.0-dividend_yields[i])); 
		};
	    };
	};
	for (int i=0; i<=step; ++i)   {
	    call_prices[i] = (pDown*call_prices[i]+pUp*call_prices[i+1])*Rinv;
	    prices[i] = d*prices[i+1];
	    call_prices[i] = max(call_prices[i], prices[i]-K);         // check for exercise
	};
    };
    return call_prices[0];
};
