#include <cmath>
#include <algorithm>
using namespace std;
#include "normdist.h"

double option_price_delta_put_european_simulated(const double& S, 
						 const double& K, 
						 const double& r,
						 const double& sigma, 
						 const double& time,
						 const int& no_sims) {
    double sigma_sqr = sigma * sigma;
    double R = (r - 0.5 * sigma_sqr)*time;
    double SD = sigma * sqrt(time);
    double sum_payoffs = 0.0;
    double sum_payoffs_2 = 0.0;
    double q = S*0.01; 
    for (int n=1; n<=no_sims; n++) {
	double Z = random_normal();
	double S_T = S * exp(R + SD * Z);
	double S_T_2 = (S+q) * exp(R + SD * Z);
	sum_payoffs += max(0.0, K-S_T);
	sum_payoffs_2 += max(0.0, K-S_T_2);
    };
    double p = exp(-r*time) * ( sum_payoffs/no_sims); 
    double p2 = exp(-r*time) * ( sum_payoffs_2/no_sims); 
    return (p2-p)/q;
};
