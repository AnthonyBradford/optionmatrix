#include <math.h>
#include <algorithm>         
#include "normdist.h"               // normal distribution
#include "fin_recipes.h"          // define other option pricing formulas
const double ACCURACY=1.0e-6;

double option_price_american_put_approximated_baw( const double& S,
						   const double& X, 
						   const double& r,
						   const double& b,
						   const double& sigma,
						   const double& time ){
    const double sigma_sqr = sigma*sigma;
    const double time_sqrt = sqrt(time);
    const double M=2.0*r/sigma_sqr; 
    const double NN=2.0*b/sigma_sqr;
    const double K=1.0-exp(-r*time);
    double q1     = 0.5*(-(NN-1)-sqrt(pow((NN-1),2.0)+(4.0*M/K)));

    // now find initial S value 
    double q1_inf = 0.5*(-(NN-1)-sqrt(pow((NN-1),2.0)+4.0*M));
    double S_star_star_inf=X/(1.0-1.0/q1_inf);
    double h1 = (b*time-2*sigma*time_sqrt)*(X/(X-S_star_star_inf));
    double S_seed=S_star_star_inf+(X-S_star_star_inf)*exp(h1);

    double Si = S_seed;  // now do Newton iterations to solve for S**
    int no_iterations = 0;
    double g          = 1;
    double gprime     = 1;
    while ((fabs(g)>ACCURACY)
	   && (fabs(gprime)>ACCURACY) // to avoid non-convergence
	   && (no_iterations++<500)
	   && Si>0.0) {
	double p = option_price_european_put_payout(Si,X,r,b,sigma,time);
	double d1 = (log(Si/X)+(b+0.5*sigma_sqr)*time)/(sigma*time_sqrt); 
	g = X - Si - p + (1-exp((b-r)*time)*N(-d1))*Si/q1;
	gprime = (1.0/q1-1.0)*(1.0-exp((b-r)*time)*N(-d1))
	    + (1.0/q1)*exp((b-r)*time)*(1.0/(sigma*time_sqrt))*n(-d1);
	Si=Si-(g/gprime);  
    };
    double S_star_star=Si;  
    if (g>ACCURACY) { 
	S_star_star = S_seed; 
    };  // if not found g**
    double P=0;
    double p = option_price_european_put_payout(S,X,r,b,sigma,time);
    if (S>S_star_star) {
	double d1 = (log(S_star_star/X)
		     + (b+0.5*sigma_sqr)*time)/(sigma*time_sqrt);
	double A1 = -(S_star_star/q1)*(1-exp((b-r)*time)*N(-d1));
	P= p + A1 * pow((S/S_star_star),q1);
    }
    else {
	P=X-S;
    };
    return max(P,p);  // should not be lower than Black Scholes value
};
