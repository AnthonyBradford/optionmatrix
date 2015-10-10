#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_trinomial_trees(){
    double S = 100.0; double K = 100.0;
    double r = 0.1;   double sigma = 0.25;
    double time=1.0;  double q=0;  
    int no_steps = 100;
    cout << " european put using binomial = "  
	 << option_price_put_european_binomial(S,K,r,sigma,time,no_steps) 
	 << endl;
    cout << " american put using binomial = " 
	 << option_price_put_american_binomial(S,K,r,sigma,time,no_steps) 
	 << endl;
    cout << " american put using trinomial = " 
	 << option_price_put_american_trinomial(S,K,r,q,sigma,time,no_steps) 
	 << endl;
}; 

void examples_trinomial_trees(){
    cout << "----------------------------" << endl;
    cout << "-- trinomial trees ---------" << endl;
    cout << "----------------------------" << endl;
    test_trinomial_trees();
};
