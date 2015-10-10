#include <cmath>
#include "fin_recipes.h"

double option_price_call_merton_jump_diffusion( const double& S, 
						const double& X,
						const double& r,
						const double& sigma, 
						const double& time_to_maturity,
						const double& lambda,
						const double& kappa,
						const double& delta) {
    const int MAXN=50;
    double tau=time_to_maturity;
    double sigma_sqr = sigma*sigma; 
    double delta_sqr = delta*delta;
    double lambdaprime = lambda * (1+kappa);
    double gamma = log(1+kappa);
    double c = exp(-lambdaprime*tau)*option_price_call_black_scholes(S,X,r-lambda*kappa,sigma,tau);
    double log_n = 0;
    for (int n=1;n<=MAXN; ++n) {
	log_n += log(double(n));
	double sigma_n = sqrt( sigma_sqr+n*delta_sqr/tau );
	double r_n = r-lambda*kappa+n*gamma/tau;
	c += exp(-lambdaprime*tau+n*log(lambdaprime*tau)-log_n)*
	    option_price_call_black_scholes(S,X,r_n,sigma_n,tau);
    };
    return c;
};
