#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_warrant_price_adjusted_black_scholes(){
    double S = 48;  double K = 40; double r = 0.08;  double sigma = 0.30;
    double time = 0.5;   double m = 1000;   double n = 10000;
    double w = warrant_price_adjusted_black_scholes(S,K,r,sigma, time, m, n);
    cout << " warrant price = " << w << endl;
};

void warrant_examples(){
    cout << "----------------------------------------" << endl;
    cout << "Warrant pricing chapter" << endl;
    cout << "----------------------------------------" << endl;
    test_warrant_price_adjusted_black_scholes();
};
