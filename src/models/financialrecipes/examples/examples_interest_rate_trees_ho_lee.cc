#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_ho_lee_pricing_european_call(){
    double delta=0.98;
    double pi=0.5;
    double r=0.1;
    term_structure_class* initial=new term_structure_class_flat(r);
    vector<double> times; times.push_back(5.0);
    vector<double> cflows; cflows.push_back(100);
    double K=80;
    double time_to_maturity=3;
    cout << " Flat term structure " << endl;
    cout << " c= " << price_european_call_option_on_bond_using_ho_lee(initial, delta, pi, times,cflows,K,time_to_maturity);
    cout << endl;
    delete (initial);
    double beta0=0.09;  double beta1=0.01; double beta2=0.01; double lambda=5.0;
    initial = new term_structure_class_nelson_siegel(beta0,beta1,beta2,lambda);
    cout << " Nelson Siegel term structure " << endl;
    cout << " c= " << price_european_call_option_on_bond_using_ho_lee(initial, delta, pi, times,cflows,K,time_to_maturity);
    cout << endl;
    delete (initial);
};

void examples_interest_rate_trees_ho_lee(){
    cout << "------------------------------------"<<endl;
    cout << "---- interest rate trees ho lee ----"<<endl;
    cout << "------------------------------------"<<endl;
    test_ho_lee_pricing_european_call();
};
