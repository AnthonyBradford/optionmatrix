#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_bermudan_option(){
    double S=80;         double K=100;          double r = 0.20;
    double time = 1.0;   double sigma = 0.25;
    int steps = 500;
    double q=0.0;
    vector<double> potential_exercise_times;  potential_exercise_times.push_back(0.25); 
    potential_exercise_times.push_back(0.5);  potential_exercise_times.push_back(0.75);
    cout << " Bermudan put price = " 
	 << option_price_put_bermudan_binomial(S,K,r,q,sigma,time,potential_exercise_times,steps)
	 << endl;
};

void test_analytical_geometric_average(){
    double S=100;  double K=100; double q=0;
    double r=0.06; double sigma=0.25; double time=1.0;
    cout << " Analytical geometric average = " 
	 << option_price_asian_geometric_average_price_call(S,K,r,q,sigma,time)
	 << endl;
};

void test_exotics_lookback(){
    double S=100; double Smin=S; double q = 0; double r = 0.06;
    double sigma = 0.346; double time = 1.0;
    cout << " Lookback call price = " 
	 << option_price_european_lookback_call(S,Smin,r,q,sigma,time) << endl;
};

void test_simulate_general_european(){
    cout << "Testing general simulation of European options " << endl;
    double S=100; double K=120; double r = 0.10;
    double time = 1.0; double sigma = 0.25; int no_sims = 10000; int no_steps = 250;
    double q=0;

    cout << " simulated arithmetric average " 
	 << " S= " <<  S << " r= " << r << " price="
	 << derivative_price_simulate_european_option_generic(S,K,r,sigma,time,
							      payoff_arithmetric_average_call,
							      no_steps,no_sims) 
	 << endl; 

    cout << " simulated geometric average = " 
	 << derivative_price_simulate_european_option_generic(S,K,r,sigma,time,
							      payoff_geometric_average_call,
							      no_steps,no_sims) 
	 << endl; 
    cout << " analytical lookback put = " 
	 << option_price_european_lookback_put(S,S,r,q,sigma,time)
	 << endl;
    cout << " simulated lookback put = " 
	 << derivative_price_simulate_european_option_generic(S,0,r,sigma,time,
							      payoff_lookback_put,
							      no_steps,no_sims) 
	 << endl; 
    cout << " analytical lookback call = " 
	 << option_price_european_lookback_call(S,S,r,q,sigma,time)
	 << endl;

    cout << " simulated lookback call = " 
	 << derivative_price_simulate_european_option_generic(S,0,r,sigma,time,
							      payoff_lookback_call,
							      no_steps,no_sims) 
	 << endl; 
    cout << " simulated lookback call using control variates = " 
	 << derivative_price_simulate_european_option_generic_with_control_variate(S,0,r,sigma,time,
										   payoff_lookback_call,
										   no_steps,no_sims) 
	 << endl; 
};

void average_and_lookback_options_examples(){
    cout << "------------------------------------" << endl;
    cout << "Average and Lookback Options " << endl;
    cout << "------------------------------------" << endl;
    test_bermudan_option();
    test_analytical_geometric_average();
    test_exotics_lookback();
    test_simulate_general_european();
};
