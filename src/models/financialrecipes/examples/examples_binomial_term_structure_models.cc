#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_rendleman_bartter_zero_coupon_call() {
    double K=950; double S=0.15; double M=0.05; double interest=0.10; 
    double option_maturity=4; double bond_maturity=5; double bond_maturity_payment=1000;
    int no_steps=100; 
    cout << " Rendleman Bartter price of option on zero coupon bond: "; 
    double c = bond_option_price_call_zero_american_rendleman_bartter( K, option_maturity, S, M, 
								       interest, bond_maturity, 
								       bond_maturity_payment, no_steps); 
    cout << " c = " << c << endl; 
};


void binomial_term_structure_models_examples(){
    cout << "---------------------------------------" << endl;
    cout << "Binomial term structure examples " << endl;
    cout << "---------------------------------------" << endl;
    test_rendleman_bartter_zero_coupon_call();    
};
