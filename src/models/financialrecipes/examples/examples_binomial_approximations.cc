#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_binomial_approximations_option_pricing(){
    double S = 100.0;    double K = 100.0;
    double r = 0.1;      double sigma = 0.25;
    double time=1.0;
    int no_steps = 100;
    cout << " european call = " 
	 << option_price_call_european_binomial(S,K,r,sigma,time,no_steps) 
	 << endl;
    cout << " american call = " 
	 << option_price_call_american_binomial(S,K,r,sigma,time,no_steps) 
	 << endl;
};

void test_binomial_approximations_option_price_partials(){
    double S = 100.0;    double K = 100.0;
    double r = 0.1;      double sigma = 0.25;
    double time=1.0;     int no_steps = 100;

    double delta, gamma, theta, vega, rho;
    option_price_partials_american_call_binomial(S,K,r, sigma, time, no_steps,
						 delta, gamma, theta, vega, rho);
    cout << " Call price partials " << endl;
    cout << "  delta = " << delta << endl;
    cout << "  gamma = " << gamma << endl;
    cout << "  theta = " << theta << endl;
    cout << "  vega  = " << vega << endl;
    cout << "  rho   = " << rho << endl;
};

void test_binomial_approximations_option_price_dividends(){
    double S = 100.0;    double K = 100.0;
    double r = 0.10;      double sigma = 0.25;
    double time=1.0;
    int no_steps = 100;
    double d=0.02;
    cout << " call price with continuous dividend payout = " 
	 << option_price_call_american_binomial(S,K,r,d,sigma,time,no_steps) << endl;
    vector<double> dividend_times;      vector<double> dividend_yields;
    dividend_times.push_back(0.25);     dividend_yields.push_back(0.025);
    dividend_times.push_back(0.75);     dividend_yields.push_back(0.025);
    cout << " call price with proportial dividend yields at discrete dates = "
	 << option_price_call_american_proportional_dividends_binomial(S,K,r,sigma,time,no_steps,
								       dividend_times, dividend_yields) 
	 << endl;

    vector<double> dividend_amounts; 
    dividend_amounts.push_back(2.5);
    dividend_amounts.push_back(2.5);
    cout << " call price with proportial dividend amounts at discrete dates = "
	 << option_price_call_american_discrete_dividends_binomial(S,K,r,sigma,time,no_steps,
								   dividend_times, dividend_amounts) 
	 << endl;
};

void test_binomial_approximations_futures_options(){
    double F = 50.0;    double K = 45.0;
    double r = 0.08;    double sigma = 0.2;
    double time=0.5;
    int no_steps=100;
    cout << " european futures call option = "
	 << futures_option_price_call_american_binomial(F,K,r,sigma,time,no_steps) << endl;
};

void test_binomial_approximations_currency_options(){
    double S = 50.0;      double K = 52.0;
    double r = 0.08;      double rf=0.05;
    double sigma = 0.2;   double time=0.5;

    int no_steps = 100;
    cout << " european currency option call = " 
	 << currency_option_price_call_american_binomial(S,K,r,rf,sigma,time,no_steps)  << endl;
};

void binomial_approximations_examples(){
    cout << "-------------------------------------" << endl;
    cout << "Binomial Approximations examples" << endl;
    cout << "-------------------------------------" << endl;
    test_binomial_approximations_option_pricing();
    test_binomial_approximations_option_price_partials();
    test_binomial_approximations_option_price_dividends();
    test_binomial_approximations_futures_options();
    test_binomial_approximations_currency_options();
};
