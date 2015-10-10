#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_explicit_finite_differences(){
    double S = 50.0;
    double K = 50.0;
    double r = 0.1; 
    double sigma = 0.4;
    double time=0.4167;
    int no_S_steps=20;
    int no_t_steps=11;
    cout << " explicit finite differences, european put price = ";
    cout << option_price_put_european_finite_diff_explicit(S,K,r,sigma,time,no_S_steps,no_t_steps) 
	 << endl;
    cout << " explicit finite differences, american put price = ";
    cout << option_price_put_american_finite_diff_explicit(S,K,r,sigma,time,no_S_steps,no_t_steps) 
	 << endl;
};

void finite_differences_examples(){
    cout << "----------------------------" << endl;
    cout << "Finite Differences examples " << endl;
    cout << "----------------------------" << endl;
    test_explicit_finite_differences();
};
