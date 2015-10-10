#include <iostream>
#include "normdist.h"

using namespace std;

void test_cumulative_normal() {
    cout << " N(0) = " << N(0) << endl;
    cout << " N(0,0,0) = " << N(0,0,0) << endl;
};

void test_random_normal(){
    cout << " 5 random uniform numbers between 0 and 1: " << endl << "    "; 
    for (int i=0;i<5;++i){ cout << " " << random_uniform_0_1(); }; cout << endl;
    cout << " 5 random normal(0,1) numbers: " << endl << "    ";
    for (int i=0;i<5;++i){ cout << " " << random_normal() ; }; cout << endl;
};

void normal_distribution_examples(){
    cout << "----------------------------------" << endl;
    cout << " Normal distribution calculations " << endl;
    cout << "----------------------------------" << endl;
    test_cumulative_normal();
    test_random_normal();
};
