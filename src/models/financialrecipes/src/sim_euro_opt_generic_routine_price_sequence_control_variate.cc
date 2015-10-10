#include "fin_recipes.h"
#include <cmath>
using namespace std;

double 
derivative_price_simulate_european_option_generic_with_control_variate(const double& S,
								       const double& K,
								       const double& r,
								       const double& sigma,
								       const double& time,
								       double payoff(const vector<double>& prices,
										     const double& X),
								       const int& no_steps,
								       const int& no_sims) {
    double c_bs = option_price_call_black_scholes(S,S,r,sigma,time);// price an at the money Black Scholes call
    double sum_payoffs=0;
    double sum_payoffs_bs=0;
    for (int n=0; n<no_sims; n++) {
	vector<double> prices = simulate_lognormally_distributed_sequence(S,r,sigma,time, no_steps);
	double S1= prices.back();
	sum_payoffs += payoff(prices,K);
	sum_payoffs_bs += payoff_call(S1,S); // simulate at the money Black Scholes price
    };
    double c_sim = exp(-r*time) * (sum_payoffs/no_sims); 
    double c_bs_sim = exp(-r*time) * (sum_payoffs_bs/no_sims); 
    c_sim += (c_bs-c_bs_sim); 
    return c_sim;
};
