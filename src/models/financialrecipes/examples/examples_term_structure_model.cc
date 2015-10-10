#include <iostream>
#include "fin_recipes.h"

using namespace std;

void test_term_structure_nelson_siegel(){
    double beta0=0.09;  double beta1=0.01; double beta2=0.01; double lambda=5.0;
    double t=1.0;
    cout << "Example calculations using the Nelson Siegel term structure approximation" << endl;
    cout << " direct calculation, yield = " 
	 << term_structure_yield_nelson_siegel(t,beta0,beta1,beta2,lambda) << endl;

    term_structure_class_nelson_siegel ns(beta0,beta1,beta2,lambda);
    cout << " using a term structure class" << endl;
    cout << " yield (t=1) = " << ns.r(t) << endl;
    cout << " discount factor (t=1) = " << ns.d(t) << endl;
    cout << " forward rate (t1=1, t2=2) = " << ns.f(1,2) << endl; 
};

void test_term_structure_cir(){
    cout << "Example calculations using the Cox Ingersoll Ross term structure model " << endl;
    double r = 0.05; double kappa=0.01; double sigma=0.1; double theta=0.08; double lambda=0.0;
    cout << " direct calculation, discount factor (t=1): " 
	 << term_structure_discount_factor_cir(1, r, kappa, lambda, theta, sigma) << endl;
    cout << " using a class " << endl;
    term_structure_class_cir cir(r,kappa,lambda,theta,sigma);
    cout << " yield (t=1) = " << cir.r(1) << endl;
    cout << " discount factor (t=1) = " << cir.d(1) << endl;
    cout << " forward (t1=1, t2=2) = "  << cir.f(1,2) << endl;
};

void test_term_structure_cubic_spline(){
    cout << "Example term structure calculations using a cubic spline " << endl;
    double b=0.1;  double c=0.1; double d=-0.1;
    vector<double> f;     f.push_back(0.01);  f.push_back(0.01);  f.push_back(-0.01);
    vector<double> knots; knots.push_back(2); knots.push_back(7); knots.push_back(12); 
    cout << " direct calculation, discount factor (t=1) "
	 << term_structure_discount_factor_cubic_spline(1,b,c,d,f,knots) << endl;
    cout << " Using a term structure class " << endl;
    term_structure_class_cubic_spline cs(b,c,d,f,knots);
    cout << " yield (t=1) = " << cs.r(1) << endl;
    cout << " discount factor (t=1) = " << cs.d(1) << endl;
    cout << " forward (t1=1, t2=2) = "  << cs.f(1,2) << endl;
};

void test_term_structure_vasicek() {
    cout << "Example term structure calculation using the Vasicek term structure model" << endl;
    double r=0.05;  double a=-0.1; double b=0.1; double sigma=0.1;
    cout << " direct calculation, discount factor (t=1): " 
	 << term_structure_discount_factor_vasicek(1, r, a, b, sigma) << endl;
    term_structure_class_vasicek vc(r,a,b,sigma);
    cout << " using a term structure class " << endl;
    cout << " yield (t=1) = " << vc.r(1) << endl;
    cout << " discount factor (t=1) = " << vc.d(1) << endl;
    cout << " forward rate (t1=1, t2=2) = " << vc.f(1,2) << endl;
}

void test_term_structure_svensson(){
    double beta0=0.01;  double beta1=0.01; double beta2=0.01; double beta3=0.01; 
    double tau1=5.0;     double tau2=5.0;
    double t=1.0;
    cout << "Example calculations using the Svensson term structure approximation" << endl;
    cout << " direct calculation, yield = " 
    	 << term_structure_yield_svensson(t,beta0,beta1,beta2,beta3,tau1,tau2) 
    	 << endl;

    term_structure_class_svensson s(beta0, beta1, beta2, beta3, tau1, tau2);
    cout << " using a term structure class" << endl;
    cout << " yield (t=1) = " << s.r(t) << endl;
    cout << " discount factor (t=1) = " << s.d(t) << endl;
    cout << " forward rate (t1=1, t2=2) = " << s.f(1,2) << endl; 
};

void term_structure_model_examples(){
    cout << "----------------------------" << endl;
    cout << "Further term structure models " << endl;
    cout << "----------------------------" << endl;
    test_term_structure_nelson_siegel(); 
    test_term_structure_svensson();
    test_term_structure_cir();
    test_term_structure_cubic_spline();
    test_term_structure_vasicek(); 
}; 
