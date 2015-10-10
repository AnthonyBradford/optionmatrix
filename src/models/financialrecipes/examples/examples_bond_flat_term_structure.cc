#include <iostream>
#include "fin_recipes.h"

using namespace std;

void example_bond_pricing_flat_term_structure(){
    vector<double> cflows; cflows.push_back(10); cflows.push_back(10); cflows.push_back(110);
    vector<double> times;  times.push_back(1);   times.push_back(2);   times.push_back(3);
    double r=0.09;
    cout << "Discrete discounting" << endl;
    double B = bonds_price_discrete(times, cflows, r);
    cout << " bonds price    = " <<  B << endl;
    cout << " bond yield to maturity = " << bonds_yield_to_maturity_discrete(times, cflows, B) << endl;
    cout << " bond duration  = " << bonds_duration_discrete(times, cflows, r) << endl;
    cout << " bond duration modified = " << bonds_duration_modified_discrete(times, cflows, B) << endl;
    cout << " bond convexity =" << bonds_convexity_discrete(times, cflows, r) << endl;
    cout << " new bond price = " << bonds_price_discrete(times, cflows, 0.1) << endl;
    cout << "Continous discounting" << endl; 
    B = bonds_price(times, cflows, r);
    cout << " bonds price    = " << B << endl;
    cout << " bond yield to maturity = " << bonds_yield_to_maturity(times, cflows, B) << endl;
    cout << " bond duration  = " << bonds_duration(times, cflows, r) << endl;
    cout << " bond convexity =" << bonds_convexity(times, cflows, r) << endl;
    cout << " new bond price = " << bonds_price(times, cflows, 0.08) << endl;
}

void bond_pricing_flat_term_structure_examples(){
    cout << "----------------------------" << endl;
    cout << "Bond Pricing with a flat term structure Chapter " << endl;
    cout << "----------------------------" << endl;
    example_bond_pricing_flat_term_structure();
};
