#include <cmath>     // standard mathematical functions
#include <algorithm>   // define the max() function
using namespace std;
#include "normdist.h"   // definition of random number generator

double option_price_delta_call_european_simulated(const double& S, 
						  const double& K, 
						  const double& r,
						  const double& sigma, 
						  const double& time,
						  const int& no_sims){
    double R = (r - 0.5 * pow(sigma,2))*time;
    double SD = sigma * sqrt(time);
    double sum_payoffs = 0.0;
    double sum_payoffs_q = 0.0;
    double q = S*0.01; 
    for (int n=1; n<=no_sims; n++) {
	double Z = random_normal();
	double S_T  = S* exp(R + SD * Z);
	sum_payoffs += max(0.0, S_T-K);
	double S_T_q = (S+q)* exp(R + SD * Z);
	sum_payoffs_q += max(0.0, S_T_q-K);
    };
    double c = exp(-r*time) * (sum_payoffs/no_sims); 
    double c_q = exp(-r*time) * (sum_payoffs_q/no_sims); 
    return (c_q-c)/q;
};
