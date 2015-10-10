#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_simulation_pricing() { 
    double S=100.0;  double K=100.0; double r=0.1; double sigma=0.25;
    double time=1.0; int no_sims=5000;
    cout << " call:  black scholes price = "  << option_price_call_black_scholes(S,K,r,sigma,time) << endl;
    cout << "        simulated price     = "  
	 << option_price_call_european_simulated(S,K,r,sigma,time,no_sims) << endl;
    cout << " put:  black scholes price = " << option_price_put_black_scholes(S,K,r,sigma,time) << endl;
    cout << "       simulated price     = " 
	 << option_price_put_european_simulated(S,K,r,sigma,time, no_sims)  << endl;
};

void test_simulation_pricing_delta(){
    double S=100.0;  double K=100.0; double r=0.1; double sigma=0.25;
    double time=1.0; int no_sims=5000;
    cout << " call: bs delta  = " << option_price_delta_call_black_scholes(S,K,r,sigma,time) 
	 << "       sim delta = " << option_price_delta_call_european_simulated(S,K,r,sigma,time,no_sims) 
	 << endl;
    cout << " put: bs delta  = " <<  option_price_delta_put_black_scholes(S,K,r,sigma,time) 
	 << "      sim delta = " <<  option_price_delta_put_european_simulated(S,K,r,sigma,time,no_sims) 
	 << endl;
};
 

void test_simulation_bs_case_using_generic_routine(){
    double S  = 100; double X = 100; double r = 0.1;
    double sigma = 0.25; double time  = 1.0;  int no_sims     = 50000;
    cout << "Black Scholes call option price = " << option_price_call_black_scholes(S,X,r,sigma,time) << endl;
    cout << "Simulated call option price     = " 
	 << derivative_price_simulate_european_option_generic(S,X,r,sigma,time,payoff_call,no_sims)
	 << endl;
    cout << "Black Scholes put option price  = " << option_price_put_black_scholes(S,X,r,sigma,time) << endl;
    cout << "Simulated put option price      = " 
	 << derivative_price_simulate_european_option_generic(S,X,r,sigma,time,payoff_put,no_sims)
	 << endl;
};
void test_simulation_bs_case_using_generic_routine_improving_efficiency(){
    double S = 100; double K = 100; double r = 0.1;
    double sigma    = 0.25; double time = 1; int no_sims     = 50000;
    cout << "Black Scholes call option price = " 
	 << option_price_call_black_scholes(S,K,r,sigma,time) << endl;
    cout << "Simulated call option price     = " 
	 << derivative_price_simulate_european_option_generic(S,K,r,sigma,time, payoff_call,no_sims)
	 << endl;
    cout << "Simulated call option price, CV = " 
	 << derivative_price_simulate_european_option_generic_with_control_variate(S,K,r,sigma,time,
										   payoff_call,no_sims)
	 << endl;
    cout << "Simulated call option price, AV = " 
	 << derivative_price_simulate_european_option_generic_with_antithetic_variate(S,K,r,sigma,time,
										      payoff_call,no_sims)
	 << endl;
    cout << "Black Scholes put option price  = " << option_price_put_black_scholes(S,K,r,sigma,time) << endl;
    cout << "Simulated put option price      = " 
	 << derivative_price_simulate_european_option_generic(S,K,r,sigma,time,payoff_put,no_sims) << endl;
    cout << "Simulated put option price,  CV = " 
	 << derivative_price_simulate_european_option_generic_with_control_variate(S,K,r,sigma,time,
										   payoff_put,no_sims)
	 << endl;
    cout << "Simulated put option price,  AV = " 
	 << derivative_price_simulate_european_option_generic_with_antithetic_variate(S,K,r,sigma,time,
										      payoff_put,no_sims)
	 << endl;
};

void test_simulation_binary_options(){
    double S=100.0; double K=100.0; double r=0.1; double sigma=0.25;
    double time=1.0;  int no_sims=5000;
    cout << " cash or nothing, Q=1: " 
	 << derivative_price_simulate_european_option_generic(S,K,r,sigma,time,
							      payoff_cash_or_nothing_call,
							      no_sims)
	 << endl;
    cout << " control_variate " 
	 << derivative_price_simulate_european_option_generic_with_control_variate(S,K,r,sigma,time,
										   payoff_cash_or_nothing_call,
										   no_sims)
	 << endl;
    cout << " antithetic_variate " 
	 << derivative_price_simulate_european_option_generic_with_antithetic_variate(S,K,r,sigma,time,
										      payoff_cash_or_nothing_call,
										      no_sims)
	 << endl;
    cout << " asset or nothing: " 
	 << derivative_price_simulate_european_option_generic(S,K,r,sigma,time,
							      payoff_asset_or_nothing_call,
							      no_sims)
	 << endl;
    cout << " control_variate " 
	 << derivative_price_simulate_european_option_generic_with_control_variate(S,K,r,sigma,time,
										   payoff_asset_or_nothing_call,
										   no_sims)
	 << endl;
    cout << " antithetic_variate " 
	 << derivative_price_simulate_european_option_generic_with_antithetic_variate(S,K,r,sigma,time,
										      payoff_asset_or_nothing_call,
										      no_sims)
	 << endl;
};

void simulation_examples(){
    cout << "--------------------------" << endl;
    cout << " Simulation examples " << endl;
    cout << "--------------------------" << endl;
    test_simulation_pricing();
    test_simulation_pricing_delta(); 
    test_simulation_bs_case_using_generic_routine();
    test_simulation_bs_case_using_generic_routine_improving_efficiency();
    test_simulation_binary_options();
};
