#include "fin_recipes.h"
#include "normdist.h"
#include <cmath>
using namespace std;

double  
derivative_price_simulate_european_option_generic_with_antithetic_variate(const double& S,
									  const double& K,
									  const double& r,
									  const double& sigma,
									  const double& time,
									  double payoff(const double& S,
											const double& X),
									  const int& no_sims) {
    double R = (r - 0.5 * pow(sigma,2) )*time;
    double SD = sigma * sqrt(time);
    double sum_payoffs=0;
    for (int n=0; n<no_sims; n++) {
	double x=random_normal();
	double S1 = S * exp(R + SD * x);
	sum_payoffs += payoff(S1,K);
	double S2 = S * exp(R + SD * (-x));
	sum_payoffs += payoff(S2,K);
    };
    return exp(-r*time) * (sum_payoffs/(2*no_sims)); 
};
