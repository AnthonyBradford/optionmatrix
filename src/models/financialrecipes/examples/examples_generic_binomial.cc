#include <iostream>
#include "fin_recipes.h"

using namespace std;

void example_binomial_generic_standard_put_and_calls(){

     double S = 100.0;
     double K = 100.0;
     double r = 0.1;
     double sigma = 0.25;
     double time_to_maturity=1.0;
     int steps = 100;
     cout << " american call price = "
          << option_price_generic_binomial(S,K,payoff_call, r, sigma, time_to_maturity, steps)
          << endl;
     cout << " american put price = "
          << option_price_generic_binomial(S,K,payoff_put, r, sigma, time_to_maturity, steps)
          << endl;
};
void example_binomial_generic_binary(){
     double S = 100.0;
     double K = 120.0;
     double r = 0.1;
     double sigma = 0.25;
     double time_to_maturity=1.0;
     int steps = 100;
     cout << " binary option price = "
          << option_price_generic_binomial(S,K,payoff_binary_call, r, sigma, time_to_maturity, steps)
          << endl;
};

void examples_generic_binomial(){
    cout << "----------------------------------------" << endl;
    cout << "Generic binomial pricing                " << endl;
    cout << "----------------------------------------" << endl;
    example_binomial_generic_standard_put_and_calls();
    example_binomial_generic_binary();
};
