#include "config.h"

#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

#ifdef HAVE_LIBGSL
 #include "gsl/gsl_integration.h"
#endif

#ifdef HAVE_LIBGSL

struct heston_parms {double K; double x; double r;  double v; double tau;  double kappa; double theta; 
                     double rho; double sigma; double lambda;  int j;};

extern "C"{
double heston_integrand_j(double phi, void *p){ 
    struct heston_parms* parms = (struct heston_parms*)p;
    double K = (parms->K); double x = (parms->x); 
    double v = (parms->v); double r = (parms->r);
    double kappa = (parms->kappa);
    double theta = (parms->theta);
    double rho = (parms->rho);
    double sigma = (parms->sigma);
    double lambda = (parms->lambda);
    double tau = (parms->tau);
    double j = (parms->j);
    double sigma_sqr = pow(sigma,2);
    double uj;    double bj;
    if (j==1){	uj=0.5;  bj=kappa+lambda-rho*sigma; }
    else {      uj=-0.5; bj=kappa+lambda;   };
    complex <double> i(0,1);
    double a = kappa*theta;
    complex<double> d  = sqrt( pow(rho*sigma*phi*i-bj,2) - sigma_sqr*(2*uj*phi*i-pow(phi,2)) );
    complex<double> g  = (bj - rho*sigma*phi*i+d)/(bj-rho*sigma*phi*i-d);
    complex<double> C  = r*phi*i*tau+(a/sigma_sqr)*((bj-rho*sigma*phi*i+d)*tau-2.0*log((1.0-g*exp(d*tau))/(1.0-g)));
    complex<double> D  = (bj-rho*sigma*phi*i+d)/sigma_sqr * ( (1.0-exp(d*tau))/(1.0-g*exp(d*tau)) );
    complex<double> f1 = exp(C+D*v+i*phi*x);
    complex<double> F  = exp(-phi*i*log(K))*f1/(i*phi);
    return real(F); 
};};

inline double heston_Pj(double S, double K, double r, double v, double tau, double sigma, 
                 double kappa, double lambda, double rho, double theta, int j){
    double x=log(S);
    struct heston_parms parms = { K, x, r, v, tau, kappa, theta, rho, sigma, lambda, j};
    size_t n=10000;
    gsl_integration_workspace* w = gsl_integration_workspace_alloc(n);
    gsl_function F;
    F.function = &heston_integrand_j;
    F.params=&parms;
    double result, error;
    gsl_integration_qagiu(&F,0,1e-7,1e-7,n,w,&result,&error);  // integral to infinity starting at zero
    gsl_integration_workspace_free(w);
    return 0.5 + result/M_PI;
};

double heston_call_option_price(const double& S, const double& K, const double& r, const double& v, 
				const double& tau, const double& rho,  const double& kappa, 
				const double& lambda,  const double& theta, const double& sigma){
    double P1 = heston_Pj(S,K,r,v,tau,sigma,kappa,lambda,rho,theta,1);
    double P2 = heston_Pj(S,K,r,v,tau,sigma,kappa,lambda,rho,theta,2);
    double C=S*P1-K*exp(-r*tau)*P2;
    return C;
};

#endif
