#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double futures_option_price_put_american_binomial( const double& F, 
						   const double& K,
						   const double& r, 
						   const double& sigma, 
						   const double& time, 
						   const int& no_steps){
    vector<double> futures_prices(no_steps+1);
    vector<double> put_values (no_steps+1);
    double t_delta= time/no_steps;
    double Rinv = exp(-r*(t_delta));
    double u = exp(sigma*sqrt(t_delta));
    double d = 1.0/u;
    double uu= u*u;
    double uInv=1.0/u;
    double pUp   = (1-d)/(u-d);
    double pDown = 1.0 - pUp;
    futures_prices[0] = F*pow(d, no_steps);
    int i;
    for (i=1; i<=no_steps; ++i) 
	futures_prices[i] = uu*futures_prices[i-1]; // terminal tree nodes
    for (i=0; i<=no_steps; ++i) put_values[i] = max(0.0, (K-futures_prices[i]));
    for (int step=no_steps-1; step>=0; --step) {
	for (i=0; i<=step; ++i)   {
	    futures_prices[i] = uInv*futures_prices[i+1];
	    put_values[i] = (pDown*put_values[i]+pUp*put_values[i+1])*Rinv;
	    put_values[i] = max(put_values[i], K-futures_prices[i]); // check for exercise
	};
    };
    return put_values[0];
};
