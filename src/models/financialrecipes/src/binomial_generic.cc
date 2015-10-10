#include <cmath>                 // standard mathematical library
#include <algorithm>             // defines the max() operator
#include <vector>                // STL vector templates
using namespace std;
    
double option_price_generic_binomial( const double& S,                       
				      const double& K,                       
				      double generic_payoff(const double& S, const double& K), 
				      const double& r,                       
				      const double& sigma,                   
				      const double& t,                       
				      const int& steps) {                    
    double R = exp(r*(t/steps));            // interest rate for each step
    double Rinv = 1.0/R;                    // inverse of interest rate
    double u = exp(sigma*sqrt(t/steps));    // up movement
    double d = 1.0/u;
    double p_up = (R-d)/(u-d);
    double p_down = 1.0-p_up;

    vector<double> prices(steps+1);       // price of underlying
    prices[0] = S*pow(d, steps);  // fill in the endnodes.
    double uu = u*u;
    for (int i=1; i<=steps; ++i) prices[i] = uu*prices[i-1];

    vector<double> values(steps+1);       // value of corresponding call 
    for (int i=0; i<=steps; ++i) values[i] = generic_payoff(prices[i],K); // payoffs at maturity

    for (int step=steps-1; step>=0; --step) {
	for (int i=0; i<=step; ++i) {
	    values[i] = (p_up*values[i+1]+p_down*values[i])*Rinv; // value by not exercising
	    prices[i] = d*prices[i+1];
	    values[i] = max(values[i],generic_payoff(prices[i],K));       // check for exercise
	};
    };
    return values[0];
};
