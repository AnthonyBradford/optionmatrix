#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_bond_option_gbm_pricing(){
    double B=100;
    double K=100;
    double r=0.05;
    double sigma=0.1;
    double time=1;
    cout << " zero coupon put option price = "
	 << bond_option_price_put_zero_black_scholes(B,K,r,sigma,time) << endl;

    vector<double> coupon_times; coupon_times.push_back(0.5);
    vector<double> coupons; coupons.push_back(1);
    cout << " coupon bond put option price = " 
	 << bond_option_price_put_coupon_bond_black_scholes(B,K,r,sigma,time,coupon_times,coupons);    
    cout << endl;

    int steps=100;
    cout << " zero coupon american put option price, binomial = " 
	 << bond_option_price_put_american_binomial(B,K,r,sigma,time,steps) << endl;
};

void bond_options_examples(){
    cout << "---------------------------------------" << endl;
    cout << "Bond option pricing, simple (GBM) case " << endl;
    cout << "---------------------------------------" << endl;
    test_bond_option_gbm_pricing();
};
