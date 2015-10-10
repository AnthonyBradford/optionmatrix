#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_termstru_transforms(){
    double t1=1;  double r_t1=0.05; double d_t1 =  term_structure_discount_factor_from_yield(r_t1,t1);
    cout << " a " << t1 << " period spot rate of " << r_t1 
	 << " corresponds to a discount factor of " << d_t1 << endl; 
    double t2=2;  double d_t2 = 0.9;
    double r_t2 =  term_structure_yield_from_discount_factor(d_t2,t2);
    cout << " a " << t2 << " period discount factor of " << d_t2 
	 << " corresponds to a spot rate of " << r_t2 << endl; 
    cout << " the forward rate between " << t1 << " and " << t2
	 << " is " << term_structure_forward_rate_from_discount_factors(d_t1,d_t2,t2-t1) 
	 << " using discount factors " << endl;
    cout << "  and is " << term_structure_forward_rate_from_yields(r_t1,r_t2,t1,t2) 
	 << " using yields " <<  endl;
};

void test_term_structure_class_flat(){
    cout << "flat term structure class " << endl;
    term_structure_class_flat ts(0.05); 
    double t1=1;
    cout << " discount factor t1 = " << t1 << ":" << ts.d(t1) << endl;
    double t2=2;
    cout << " discount factor t2 = " << t2 << ":" << ts.d(t2) << endl;
    cout << " spot rate t = " << t1 << ":" << ts.r(t1) << endl;
    cout << " spot rate t = " << t2 << ":" << ts.r(t2) << endl;
    cout << " forward rate from t1= " << t1 << " to t2= " << t2 << ":" << ts.f(t1,t2) << endl;
};

void test_termstru_interpolated(){
    vector<double> times; 
    vector<double> yields; 
    times.push_back(0.1);  times.push_back(0.5);  times.push_back(1); 
    yields.push_back(0.1); yields.push_back(0.2); yields.push_back(0.3);
    times.push_back(5);    times.push_back(10);
    yields.push_back(0.4); yields.push_back(0.5);
    cout << " testing interpolated term structure" << endl;
    cout << " yields at times: " << endl;
    cout << " t=.1 " << term_structure_yield_linearly_interpolated(0.1,times,yields) << endl;
    cout << " t=0.5 " << term_structure_yield_linearly_interpolated(0.5,times,yields) << endl;
    cout << " t=1 " << term_structure_yield_linearly_interpolated(1,times,yields) << endl;
    cout << " t=3 " << term_structure_yield_linearly_interpolated(3,times,yields) << endl;
    cout << " t=5 " << term_structure_yield_linearly_interpolated(5,times,yields) << endl; 
    cout << " t=10 " << term_structure_yield_linearly_interpolated(10,times,yields) << endl;
};


void test_term_structure_class_interpolated(){
    vector<double> times;     times.push_back(0.1);     
    vector<double> spotrates; spotrates.push_back(0.05);
    times.push_back(1);       times.push_back(5);
    spotrates.push_back(0.07);spotrates.push_back(0.08);
    term_structure_class_interpolated ts(times,spotrates);
    double t1=1;
    cout << "discount factor t1 = " << t1 << ":" << ts.d(t1) << endl;
    double t2=2;
    cout << "discount factor t2 = " << t2 << ":" << ts.d(t2) << endl;
    cout << "spot rate t = " << t1 << ":" << ts.r(t1) << endl;
    cout << "spot rate t = " << t2 << ":" << ts.r(t2) << endl;
    cout << "forward rate from t1= " << t1 << " to t2= " << t2 << ":" << ts.f(t1,t2) <<endl;
};


void test_term_structure_class_bond_calculations(){
  vector <double> times;     times.push_back(1);       times.push_back(2);
  vector <double> cashflows; cashflows.push_back(10);  cashflows.push_back(110);
  term_structure_class_flat tsflat(0.1);
  cout << " price = "  <<  bonds_price (times, cashflows, tsflat)  << endl;
  cout << " duration = "  <<  bonds_duration(times, cashflows, tsflat) << endl;
  cout << " convexity = "  <<  bonds_convexity(times, cashflows, tsflat) << endl;
};


void term_structure_examples(){
    cout << "--------------------------------------------" << endl;
    cout << " Term structure of interest rates examples  " << endl;
    cout << "--------------------------------------------" << endl;
    test_termstru_transforms();
    test_term_structure_class_flat();
    test_termstru_interpolated();
    test_term_structure_class_interpolated();
    test_term_structure_class_bond_calculations();
};
