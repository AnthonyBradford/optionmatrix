#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double currency_option_price_call_american_binomial(const double& S, 
						    const double& K, 
						    const double& r, 
						    const double& r_f, 
						    const double& sigma, 
						    const double& time, 
						    const int& no_steps) {
    vector<double> exchange_rates(no_steps+1);
    vector<double> call_values(no_steps+1);
    double t_delta= time/no_steps;
    double Rinv = exp(-r*(t_delta));
    double u = exp(sigma*sqrt(t_delta));
    double d = 1.0/u;
    double uu= u*u;
    double pUp   = (exp((r-r_f)*t_delta)-d)/(u-d); // adjust for foreign int.rate 
    double pDown = 1.0 - pUp;
    exchange_rates[0] = S*pow(d, no_steps);
    int i;
    for (i=1; i<=no_steps; ++i) {
	exchange_rates[i] = uu*exchange_rates[i-1]; // terminal tree nodes
    }
    for (i=0; i<=no_steps; ++i) call_values[i] = max(0.0, (exchange_rates[i]-K));
    for (int step=no_steps-1; step>=0; --step) {
	for (i=0; i<=step; ++i)   {
	    exchange_rates[i] = d*exchange_rates[i+1];
	    call_values[i] = (pDown*call_values[i]+pUp*call_values[i+1])*Rinv;
	    call_values[i] = max(call_values[i], exchange_rates[i]-K); // check for exercise
	};
    };
    return call_values[0];
};
