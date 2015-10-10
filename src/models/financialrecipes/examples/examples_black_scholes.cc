#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_option_price_call_black_scholes(){
    double S = 50; double K = 50; double r = 0.10;
    double sigma = 0.30; double time=0.50;
    cout << " Black Scholes call price = ";
    cout << option_price_call_black_scholes(S, K , r, sigma, time) << endl;
};
void test_black_scholes_partials_call(){
    cout  << " Black Scholes call partial derivatives " << endl;
    double S = 50; double K = 50; double r = 0.10;
    double sigma = 0.30; double time=0.50;
    double Delta, Gamma, Theta, Vega, Rho;
    option_price_partials_call_black_scholes(S,K,r,sigma, time,
					     Delta, Gamma, Theta, Vega, Rho);
    cout << "  Delta = " << Delta << endl;
    cout << "  Gamma = " << Gamma << endl;
    cout << "  Theta = " << Theta << endl;
    cout << "  Vega  = " << Vega << endl;
    cout << "  Rho   = " << Rho << endl;
};

void test_black_scholes_implied_volatility(){
    double S = 50; double K = 50; double r = 0.10; double time=0.50;
    double C=2.5;
    cout << " Black Scholes implied volatility using Newton search = ";
    cout << option_price_implied_volatility_call_black_scholes_newton(S,K,r,time,C) << endl;
    cout << " Black Scholes implied volatility using bisections = ";
    cout << option_price_implied_volatility_call_black_scholes_bisections(S,K,r,time,C) << endl;
};

void black_scholes_examples(){
    cout << "----------------------------------------" << endl;
    cout << "Examples in Black Scholes chapter " << endl; 
    cout << "----------------------------------------" << endl;
    test_option_price_call_black_scholes();
    test_black_scholes_partials_call();
    test_black_scholes_implied_volatility();
};
