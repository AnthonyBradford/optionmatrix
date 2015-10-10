#include "config.h"

#include <iostream>

#include "fin_recipes.h"

using namespace std;

void test_merton_jump_diff_call(){
    double S=100; double K=100; double r=0.05;
    double sigma=0.3; 
    double time_to_maturity=1;
    double lambda=0.5;
    double kappa=0.5;
    double delta=0.5;
    cout << " Merton Jump diffusion call = " 
	 << option_price_call_merton_jump_diffusion(S,K,r,sigma,time_to_maturity,lambda,kappa,delta)
	 << endl;
};

#ifdef HAVE_LIBGSL

void test_heston(){
    double S=100;
    double K=100;
    double r=0.01;
    double v=0.01;
    double tau=0.5;
    double rho=0;
    double kappa=2;
    double lambda=0.0;
    double theta=0.01;
    double sigma=0.01;
    cout << " heston call price " << heston_call_option_price( S, K, r, v, tau, rho, kappa, lambda, theta, sigma) << endl;
};

#endif


void alternative_formulas_examples(){
    cout << "-----------------------------" << endl;
    cout << "Alternative formulas " << endl;
    cout << "-----------------------------" << endl;
    test_merton_jump_diff_call();

#ifdef HAVE_LIBGSL
    test_heston();
#else
    cout << "\nGSL library needed for:\ntest_heston()\n";
#endif

};
