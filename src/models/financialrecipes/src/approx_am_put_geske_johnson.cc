#include <cmath>
#include "normdist.h"
#include "fin_recipes.h"
#include <iostream>

const double ACCURACY=1e-6;

inline double d1(const double& S,const double& X, const double& r, const double& sigma, const double& tau){
    return (log(S/X) + (r+0.5*pow(sigma,2))*tau)/(sigma*sqrt(tau));
};

inline double d2(const double& S, const double& X, const double& r, const double& sigma, const double& tau){
    return d1(S,X,r,sigma,tau)-sigma*sqrt(tau);
};

inline double calcP2(const double& S, const double& X, const double& r, const double& sigma, const double& time, 
		     const double& t2, const double& S2_bar, const double& rho12){
    double P2 = X*exp(-r*t2)*N(-d2(S,S2_bar,r,sigma,t2));
    P2 -= S*N(-d1(S,S2_bar,r,sigma,t2));
    P2 += X*exp(-r*time)*N(d2(S,S2_bar,r,sigma,t2),-d2(S,X,r,sigma,time),-rho12);
    P2 -= S*N(d1(S,S2_bar,r,sigma,t2),-d1(S,X,r,sigma,time),-rho12);
    return P2;
};

double option_price_american_put_approximated_geske_johnson( const double& S, const double& X, const double& r, 
							     const double& sigma, const double& time ){
    double P1 = option_price_put_black_scholes(S,X,r,sigma,time); 
    double rho12=1.0/sqrt(2.0);     double rho13=1.0/sqrt(3.0);     double rho23=sqrt(2.0/3.0);
    double t2 = time/2.0;    double t23 = time*2.0/3.0;    double t3 = time/3.0;
    double Si=S;     double S2_bar=S;
    double g=1;       double gprime=1;
    while (fabs(g)>ACCURACY){
	g=Si-X+option_price_put_black_scholes(Si,X,r,sigma,t2);
	gprime=1.0+option_price_delta_put_black_scholes(Si,X,r,sigma,t2);
	S2_bar=Si;
	Si=Si-g/gprime;
    }; 
    double P2 = calcP2(S,X,r,sigma,time,t2,S2_bar,rho12);
    P2=max(P1,P2); // for safety, use one less step as lower bound
    double S23_bar=S2_bar;
    g=1;
    while (fabs(g)>ACCURACY){
	g=Si-X+option_price_put_black_scholes(Si,X,r,sigma,t23);
	gprime=1.0+option_price_delta_put_black_scholes(Si,X,r,sigma,t23);
	S23_bar=Si;
	Si=Si-g/gprime;
    };
    double S3_bar=S23_bar;
    g=1;
    while (fabs(g)>ACCURACY){
	g=Si-X+option_price_put_black_scholes(Si,X,r,sigma,t3);
	gprime=1.0+option_price_delta_put_black_scholes(Si,X,r,sigma,t3);
	S3_bar=Si;
	Si=Si-g/gprime;
    };
    double P3 = X * exp(-r*t3) * N(-d2(S,S3_bar,r,sigma,t3));
    P3 -= S * N(-d1(S,S3_bar,r,sigma,t3));
    P3 += X*exp(-r*time)*N(d2(S,S3_bar,r,sigma,t3),-d2(S,S23_bar,r,sigma,t23),-rho12);
    P3 -= S*N(d1(S,S3_bar,r,sigma,t3),-d1(S,S23_bar,r,sigma,t23),-rho12);
    P3 +=  X*exp(-r*t23)*N3(d1(S,S3_bar,r,sigma,t3),d1(S,S23_bar,r,sigma,t23),-d1(S,X,r,sigma,time),rho12,-rho13,-rho23);
    P3 -= S*N3(d2(S,S3_bar,r,sigma,t3),d2(S,S23_bar,r,sigma,t23),-d2(S,X,r,sigma,time),rho12,-rho13,-rho23);
    P3=max(P2,P3); // for safety, use one less step as lower bound
    return P3+3.5*(P3-P2)-0.5*(P2-P1);
};
