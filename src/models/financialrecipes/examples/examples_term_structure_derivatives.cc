#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_vasicek_option_pricing(){
    double a = 0.1;  double b = 0.1; double sigma = 0.02; double r = 0.05; double X=0.9;
    cout << " Vasicek call option price " 
	 << bond_option_price_call_zero_vasicek(X,r,1,5,a,b,sigma) << endl;
};

void term_structure_derivatives_examples(){
    cout << "--------------------------------------" << endl;
    cout << " term structure derivatives examples  " << endl;
    cout << "--------------------------------------" << endl;
    test_vasicek_option_pricing();
}
