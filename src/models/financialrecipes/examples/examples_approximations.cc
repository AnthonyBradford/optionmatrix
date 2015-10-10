#include <iostream>
#include "fin_recipes.h"

using namespace std;

void tst_johnson_approximation_am_put(){
    double r=0.125;    double S=1.1;    double X=1;
    double sigma=0.5;    double time = 1;
    cout << " American put price using Johnson approximation = "
         << option_price_american_put_approximated_johnson(S, X, r, sigma, time)
	 << endl;
};

void test_baw_approximation_call(){
    double S = 100;   double X = 100;     double sigma = 0.20;
    double r = 0.08;  double b = -0.04;   double time = 0.25;
    cout << " Call price using Barone-Adesi Whaley approximation = " 
	 << option_price_american_call_approximated_baw(S,X,r,b,sigma,time) << endl;
};

void approximations_examples(){
    cout << "------------------------------------"<< endl;
    cout << "Approximations chapter " << endl;
    cout << "------------------------------------"<< endl;
    tst_johnson_approximation_am_put();
    test_baw_approximation_call();
};
    
