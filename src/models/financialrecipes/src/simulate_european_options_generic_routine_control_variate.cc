#include <cmath>
using namespace std;
#include "fin_recipes.h"

double 
derivative_price_simulate_european_option_generic_with_control_variate(const double& S,
								       const double& X,
								       const double& r,
								       const double& sigma,
								       const double& time,
								       double payoff(const double& S,
										     const double& X),
								       const int& no_sims) {
    double c_bs = option_price_call_black_scholes(S,S,r,sigma,time);// price an at the money Black Scholes call
    double sum_payoffs=0;
    double sum_payoffs_bs=0;
    for (int n=0; n<no_sims; n++) {
	double S_T= simulate_lognormal_random_variable(S,r,sigma,time);
	sum_payoffs += payoff(S_T,X);
	sum_payoffs_bs += payoff_call(S_T,S); // simulate at the money Black Scholes price
    };
    double c_sim = exp(-r*time) * (sum_payoffs/no_sims);
    double c_bs_sim = exp(-r*time) * (sum_payoffs_bs/no_sims);
    c_sim += (c_bs-c_bs_sim); 
    return c_sim;
};
