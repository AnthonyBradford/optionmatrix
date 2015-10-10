#include <cmath>
#include "fin_recipes.h"

double option_price_american_put_approximated_johnson( const double& S,
						       const double& X, 
						       const double& r,
						       const double& sigma,
						       const double& time ){
    double sigma_sqr=pow(sigma,2);
    double a0= 3.9649 ;
    double a1 = 0.032325;
    double b0 = 1.040803;
    double b1 = 0.00963;
    double gamma = 2*r/sigma_sqr;
    double m = (sigma_sqr*time)/(b0*sigma_sqr*time+b1);
    double Sc = X * pow (((gamma)/(1+gamma)),m);
    double l = (log(S/Sc))/(log(X/Sc) );
    double alpha = pow( ( (r*time)/(a0*r*time+a1) ), l );
    double P = alpha*option_price_put_black_scholes(S,X*exp(r*time),r,sigma,time) 
	+ (1-alpha)*option_price_put_black_scholes(S,X,r,sigma,time);
    double p=option_price_put_black_scholes(S,X,r,sigma,time);  // for safety use the Black Scholes as lower bound
    return max(p,P);
};
