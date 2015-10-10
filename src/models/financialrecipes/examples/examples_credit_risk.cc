#include <iostream>

#include "fin_recipes.h"
#include <cmath>

using namespace std;

void test_credit_risk(){
    cout << " Credit Risk Calculation " << endl;
    double V=100; double F=90; double r=0.05; double T=1; double sigma=0.25;
    double p = option_price_put_black_scholes(V,F,r,sigma,T);
    cout << " Debt value = " << exp(-r*T)*F - p << endl;
};

void credit_risk_examples(){
    cout << "------------------------------" << endl;
    cout << "Credit Risk Examples " << endl;
    cout << "------------------------------" << endl;
    test_credit_risk(); 
};
