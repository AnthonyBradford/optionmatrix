#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_bin_eur_call_ud (){
    double S = 100.0;    double K = 100.0;    double r = 0.025;
    double u = 1.05;     double d = 1/u;      
    cout << " one period european call =  " 	 
	 << option_price_call_european_binomial_single_period(S,K,r,u,d) << endl;
    int no_periods = 2; 
    cout << " two period european call =  " 
	 << option_price_call_european_binomial_multi_period_given_ud(S,K,r,u,d,no_periods) << endl;

};

void binomial_examples(){
    cout << "----------------------------" << endl;
    cout << "Binomial Chapter " << endl;
    cout << "----------------------------" << endl;
    test_bin_eur_call_ud();
};
