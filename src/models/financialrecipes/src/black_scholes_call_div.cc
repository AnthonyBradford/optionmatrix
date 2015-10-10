#include <cmath>              // mathematical library
#include <vector>
#include "fin_recipes.h"          // define the black scholes price 

double option_price_european_call_dividends( const double& S,               
					     const double& K,
					     const double& r,
					     const double& sigma,           
					     const double& time_to_maturity,
					     const vector<double>& dividend_times,
					     const vector<double>& dividend_amounts ) {  
    double adjusted_S = S;
    for (int i=0;i<dividend_times.size();i++) {
	if (dividend_times[i]<=time_to_maturity){
	    adjusted_S -= dividend_amounts[i] * exp(-r*dividend_times[i]);
	};
    };
    return option_price_call_black_scholes(adjusted_S,K,r,sigma,time_to_maturity);
};
