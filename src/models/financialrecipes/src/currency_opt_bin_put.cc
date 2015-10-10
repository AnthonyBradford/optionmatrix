#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double currency_option_price_put_american_binomial(const double& S, 
						   const double& K, 
						   const double& r, 
						   const double& r_f,
						   const double& sigma,
						   const double& time,
						   const int& no_steps) {
    vector<double> exchange_rates(no_steps+1);
    vector<double> put_values(no_steps+1);
    const double t_delta= time/no_steps;
    double Rinv = exp(-r*(t_delta));
    double u = exp(sigma*sqrt(t_delta));
    double d = 1.0/u;
    double uu= u*u;
    double pUp = (exp((r-r_f)*t_delta)-d)/(u-d); // adjust for foreign int.rate
    double pDown = 1.0 - pUp;
    exchange_rates[0] = S*pow(d, no_steps);
    int i;
    for (i=1; i<=no_steps; ++i) 
	exchange_rates[i] = uu*exchange_rates[i-1]; // terminal tree nodes
    for (i=0; i<=no_steps; ++i) put_values[i] = max(0.0, (K-exchange_rates[i]));
    for (int step=no_steps-1; step>=0; --step) {
	for (i=0; i<=step; ++i)   {
	    exchange_rates[i] = d*exchange_rates[i+1];
	    put_values[i] = (pDown*put_values[i]+pUp*put_values[i+1])*Rinv;
	    put_values[i] = max(put_values[i], K-exchange_rates[i]); // check for exercise
	};
    };
    return put_values[0];
};
