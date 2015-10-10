#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_black_scholes_with_dividends(){
    double S = 100.0;    double K = 100.0;
    double r = 0.1;      double sigma = 0.25;
    double time=1.0;
    double dividend_yield=0.05;
    vector<double> dividend_times;     vector<double> dividend_amounts; 
    dividend_times.push_back(0.25);    dividend_amounts.push_back(2.5); 
    dividend_times.push_back(0.75);    dividend_amounts.push_back(2.5);
    cout << " european stock call option with contininous dividend = "
	 << option_price_european_call_payout(S,K,r,dividend_yield,sigma,time) << endl;
    cout << " european stock call option with discrete dividend =  "
	 << option_price_european_call_dividends(S,K,r,sigma,time,dividend_times,dividend_amounts) << endl;
};

void test_rgw_price_am_call_div(){
    double S = 100.0;    double K = 100.0;    
    double r = 0.1;      double sigma = 0.25; 
    double tau = 1.0;    double tau1 = 0.5;
    double D1 = 10.0;
    cout << " american call price with one dividend = " 
	 << option_price_american_call_one_dividend(S,K,r,sigma,tau,D1, tau1)<< endl;
};

void test_futures_option_price_black(){
    double F = 50.0;    double K = 45.0;
    double r = 0.08;    double sigma = 0.2;
    double time=0.5;
    cout << " european futures call option = "
	 << futures_option_price_put_european_black(F,K,r,sigma,time) << endl;
};

void test_currency_option_european_call(){
    double S = 50.0;      double K = 52.0;
    double r = 0.08;      double rf=0.05;
    double sigma = 0.2;   double time=0.5;
    cout << " european currency call option = "
	 << currency_option_price_call_european(S,K,r,rf,sigma,time) << endl;
};

void test_option_price_perpetual_american_call(){
    double S=50.0;    double K=40.0;    
    double r=0.05;    double q=0.02;    
    double sigma=0.05;
    double price = option_price_american_perpetual_call(S,K,r,q,sigma); 
    cout << " perpetual call price = " <<  price << endl;
};

void black_scholes_extensions_examples(){
    cout << "-------------------------------" << endl;
    cout << "Black Scholes extensions" << endl;
    cout << "-------------------------------" << endl;
    test_black_scholes_with_dividends();
    test_futures_option_price_black();
    test_currency_option_european_call();
    test_rgw_price_am_call_div();
    test_option_price_perpetual_american_call();
};
