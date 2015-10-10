#include <iostream>
#include "fin_recipes.h"

using namespace std;

void example_interest_rate_trees_gbm_build_tree(){
     vector< vector<double> > tree = interest_rate_trees_gbm_build(0.1,1.02,0.99,3);
     cout << " Interest rate tree: " << endl;
     cout << " Time 0: " << tree[0][0] << endl;
     cout << " Time 1: " << tree[1][0] << "  " << tree[1][1] << endl;
     cout << " Time 2: " << tree[2][0] << "  " << tree[2][1] << "  " << tree[2][2] << endl;
};

void example_interest_rate_trees_gbm_price_bond(){
    double r0=0.1;
    double u=1.02;  double d=0.99;
    int n=3;
    double q=0.5;
    vector< vector<double> > tree = interest_rate_trees_gbm_build(r0,u,d,n);
    vector<double> cashflows;
    cashflows.push_back(0); cashflows.push_back(10); cashflows.push_back(10); cashflows.push_back(110);
    cout << "Bond price B = " << interest_rate_trees_gbm_value_of_cashflows(cashflows,tree,q) << endl;
};

void example_interest_rate_trees_gbm_price_callable_bond(){
    double r0=0.06;
    double u=1.2;  double d=0.9;
    int n=10;
    double q=0.5;
    vector< vector<double> > tree = interest_rate_trees_gbm_build(r0,u,d,n);
    vector<double> cashflows;
    cashflows.push_back(0);
    for (int t=1;t<=9;++t){ cashflows.push_back(6); };
    cashflows.push_back(106);
    cout << "Straight bond price  = " << interest_rate_trees_gbm_value_of_cashflows(cashflows,tree,q) << endl;
    int first_call_time = 6;
    double call_price = 106;
    cout << "Callable bond price = "
	 << interest_rate_trees_gbm_value_of_callable_bond(cashflows,tree,q, first_call_time, call_price) << endl;
};

void examples_interest_rate_trees_gbm(){
    cout << "-----------------------------" << endl;
    cout << "Interest rate trees " << endl;
    cout << "-----------------------------" << endl;
    example_interest_rate_trees_gbm_build_tree();
    example_interest_rate_trees_gbm_price_bond();
    example_interest_rate_trees_gbm_price_callable_bond();

};
