#include <iostream>
#include <vector>
#include "fin_recipes.h"

using namespace std;

void test_present_value(){
    vector<double> cflows; cflows.push_back(-100.0); cflows.push_back(10.0); cflows.push_back(110.0);
    vector<double> times; times.push_back(0.0); times.push_back(1); times.push_back(2);
    double r=0.05;
    cout << " present value, 5\% discretely compounded interest = " ;
    cout << cash_flow_pv_discrete(times, cflows, r) << endl;
    cout << " internal rate of return, discrete compounding = ";  
    cout <<  cash_flow_irr_discrete(times, cflows) << endl;
    cout << " present value, 5\% continously compounded interest = " ;
    cout << cash_flow_pv(times, cflows, r) << endl;
    cout << " internal rate of return, continous compounding = ";  
    cout <<  cash_flow_irr(times, cflows) << endl;
};

void present_value_examples(){
    cout << "----------------------------" << endl;
    cout << "Present Value Chapter " << endl;
    cout << "----------------------------" << endl;
    test_present_value();
};
