#include <cmath>
using namespace std;
#include "fin_recipes.h"

double derivative_price_simulate_european_option_generic(const double& S,
						  const double& K, 
						  const double& r, 
						  const double& sigma, 
						  const double& time, 
						  double payoff(const double& price, const double& X), 
						  const int& no_sims) { 
    double sum_payoffs=0;
    for (int n=0; n<no_sims; n++) {
       double S_T = simulate_lognormal_random_variable(S,r,sigma,time);
       sum_payoffs += payoff(S_T,K);
    };
    return exp(-r*time) * (sum_payoffs/no_sims); 
};
