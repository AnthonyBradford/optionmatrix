#include "fin_recipes.h"
#include "normdist.h"
#include <cmath>

const double EPSILON=0.00001;

double warrant_price_adjusted_black_scholes(const double& S, 
					    const double& K, 
					    const double& r, 
					    const double& sigma, 
					    const double& time, 
					    const double& m, // number of warrants outstanding
					    const double& n){ // number of shares outstanding
    double time_sqrt = sqrt(time);
    double w = (n/(n+m))*option_price_call_black_scholes(S,K,r,sigma,time);
    double g = w-(n/(n+m))*option_price_call_black_scholes(S+(m/n)*w,K,r,sigma,time);
    while (fabs(g)>EPSILON) {
	double d1 = (log((S+(m/n))/K)+r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt; 
	double gprime = 1-(m/n)*N(d1);
	w=w-g/gprime;
	g = w-(n/(n+m))*option_price_call_black_scholes(S+(m/n)*w,K,r,sigma,time);
    };
    return w;
};
