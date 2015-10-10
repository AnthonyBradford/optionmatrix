#include "config.h"

#include <iostream>
#include "fin_recipes.h"

using namespace std;

#ifdef HAVE_NEWMAT_NEWMAT_H
 #include <newmat/newmat.h>
 #include "fin_recipes_newmat.h"
#endif

#ifdef HAVE_NEWMAT_NEWMAT_H

void test_mean_variance_calculations_newmat(){
    cout << "Simple example of mean variance calculations, using newmat " << endl;
    Matrix e(2,1); e(1,1)=0.05; e(2,1)=0.1;
    Matrix V(2,2);
    V(1,1)=1.0; V(2,1)=0.0;
    V(1,2)=0.0; V(2,2)=1.0;
    Matrix w(2,1);
    w(1,1)=0.5;
    w(2,1)=0.5;
    cout << " mean "     << mv_calculate_mean(e,w)     << endl;
    cout << " variance " << mv_calculate_variance(V,w) << endl;
    cout << " stdev "    << mv_calculate_st_dev(V,w)   << endl;
};

void test_mean_variance_portfolio_calculation_newmat(){
    cout << "Calculate mean variance portfolio using newmat: " << endl;
    Matrix e(2,1); 
    e(1,1)=0.05; e(2,1)=0.1;
    Matrix V(2,2);
    V(1,1)=1.0; V(2,1)=0.0;
    V(1,2)=0.0; V(2,2)=1.0;
    double r=0.075;
    Matrix w = mv_calculate_portfolio_given_mean_unconstrained(e,V,r);
    cout << " suggested portfolio:  ";
    cout << " w1 = " << w(1,1) << " w2 = " << w(2,1) << endl;
};

void examples_mean_variance_newmat() {
    cout << "-------------------------------" << endl;
    cout << "Mean Variance Examples using newmat " << endl;
    cout << "-------------------------------" << endl;

    test_mean_variance_calculations_newmat();
    test_mean_variance_portfolio_calculation_newmat();
};

#endif
