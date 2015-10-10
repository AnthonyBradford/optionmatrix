#include <cmath>
using namespace std;
#include "fin_recipes.h"

double 
derivative_price_simulate_european_option_generic(const double& S, 
						  const double& K, 
						  const double& r, 
						  const double& sigma, 
						  const double& time,
						  double payoff(const vector<double>& prices, const double& X), 
						  const int& no_steps, 
						  const int& no_sims) {
    double sum_payoffs=0;
    for (int n=0; n<no_sims; n++) {
	vector<double>prices = simulate_lognormally_distributed_sequence(S,r,sigma,time,no_steps);
	sum_payoffs += payoff(prices,K);
    };
    return exp(-r*time) * (sum_payoffs/no_sims); 
};
