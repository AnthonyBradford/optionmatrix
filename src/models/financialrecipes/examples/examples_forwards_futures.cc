#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_futures_price(){
    double S=100;    double r=0.10;    double time=0.5;
    cout << " futures price = " << futures_price(S,r, time) << endl;
};

void forwards_futures_examples(){
    cout << "---------------------------" << endl;
    cout << "Futures/Forwards pricing   " << endl;
    cout << "---------------------------" << endl;
    test_futures_price();
};
