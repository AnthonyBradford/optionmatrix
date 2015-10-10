#include <cmath>
#include <vector>
#include "fin_recipes.h"
#include <iostream>
double option_price_call_american_discrete_dividends_binomial(const double& S, 
							      const double& K,
							      const double& r,
							      const double& sigma, 
							      const double& t, 
							      const int& steps,
							      const vector<double>& dividend_times,
							      const vector<double>& dividend_amounts) {
    int no_dividends = dividend_times.size();
    if (no_dividends==0) return option_price_call_american_binomial(S,K,r,sigma,t,steps);// just do regular
    int steps_before_dividend = (int)(dividend_times[0]/t*steps);
    const double R = exp(r*(t/steps));
    const double Rinv = 1.0/R;
    const double u = exp(sigma*sqrt(t/steps));
    const double d = 1.0/u;
    const double pUp   = (R-d)/(u-d);
    const double pDown = 1.0 - pUp;
    double dividend_amount = dividend_amounts[0];
    vector<double> tmp_dividend_times(no_dividends-1);  // temporaries with 
    vector<double> tmp_dividend_amounts(no_dividends-1);  // one less dividend
    for (int i=0;i<(no_dividends-1);++i){ 
	tmp_dividend_amounts[i] = dividend_amounts[i+1];
	tmp_dividend_times[i]   = dividend_times[i+1] - dividend_times[0];
    };
    vector<double> prices(steps_before_dividend+1);
    vector<double> call_values(steps_before_dividend+1);
    prices[0] = S*pow(d, steps_before_dividend);
    for (int i=1; i<=steps_before_dividend; ++i) prices[i] = u*u*prices[i-1];
    for (int i=0; i<=steps_before_dividend; ++i){
	double value_alive  
	    = option_price_call_american_discrete_dividends_binomial(prices[i]-dividend_amount,K, r, sigma,
								     t-dividend_times[0],// time after first dividend
								     steps-steps_before_dividend, 
								     tmp_dividend_times,
								     tmp_dividend_amounts);
	call_values[i] = max(value_alive,(prices[i]-K));  // compare to exercising now
    };
    for (int step=steps_before_dividend-1; step>=0; --step) {
	for (int i=0; i<=step; ++i)   {
	    prices[i] = d*prices[i+1];
	    call_values[i] = (pDown*call_values[i]+pUp*call_values[i+1])*Rinv;
	    call_values[i] = max(call_values[i], prices[i]-K); 
	};
    };
    return call_values[0];
};
