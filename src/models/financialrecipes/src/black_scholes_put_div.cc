#include <cmath>              // mathematical library
#include "fin_recipes.h"          // define the black scholes price 
#include <vector> 

double option_price_european_put_dividends( const double& S, // spot price
					    const double& X, // Strike (exercise) price,
					    const double& r,  // interest rate
					    const double& sigma,
					    const double& time_to_maturity,
					    const vector<double>& dividend_times,
					    const vector<double>& dividend_amounts ) {
    // reduce the current stock price by the amount of dividends. 
    double adjusted_S=S;
    for (unsigned int i=0;i<dividend_times.size();i++) {
	if (dividend_times[i]<=time_to_maturity){
	    adjusted_S -= dividend_amounts[i] * exp(-r*dividend_times[i]);
	};
    };
    return option_price_put_black_scholes(adjusted_S,X,r,sigma,time_to_maturity);
};
