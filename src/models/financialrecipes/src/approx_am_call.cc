#include <cmath>
#include <algorithm> 
using namespace std;        
#include "normdist.h"               // normal distribution
#include "fin_recipes.h"         // define other option pricing formulas

const double ACCURACY=1.0e-6;

double option_price_american_call_approximated_baw( const double& S,
						    const double& X, 
						    const double& r,
						    const double& b,
						    const double& sigma,
						    const double& time) {
    double sigma_sqr = sigma*sigma;
    double time_sqrt = sqrt(time);
    double nn = 2.0*b/sigma_sqr; 
    double m = 2.0*r/sigma_sqr;  
    double K = 1.0-exp(-r*time); 
    double q2 = (-(nn-1)+sqrt(pow((nn-1),2.0)+(4*m/K)))*0.5;

    double q2_inf = 0.5 * ( -(nn-1) + sqrt(pow((nn-1),2.0)+4.0*m));    // seed value from paper
    double S_star_inf = X / (1.0 - 1.0/q2_inf);
    double h2 = -(b*time+2.0*sigma*time_sqrt)*(X/(S_star_inf-X));
    double S_seed = X + (S_star_inf-X)*(1.0-exp(h2));

    int no_iterations=0; // iterate on S to find S_star, using Newton steps
    double Si=S_seed;         
    double g=1;
    double gprime=1.0;
    while ((fabs(g) > ACCURACY) 
	   && (fabs(gprime)>ACCURACY) // to avoid exploding Newton's  
	   && ( no_iterations++<500)
	   && (Si>0.0)) {
	double c  = option_price_european_call_payout(Si,X,r,b,sigma,time);
	double d1 = (log(Si/X)+(b+0.5*sigma_sqr)*time)/(sigma*time_sqrt);
	g=(1.0-1.0/q2)*Si-X-c+(1.0/q2)*Si*exp((b-r)*time)*N(d1);
	gprime=( 1.0-1.0/q2)*(1.0-exp((b-r)*time)*N(d1))
	    +(1.0/q2)*exp((b-r)*time)*n(d1)*(1.0/(sigma*time_sqrt));
	Si=Si-(g/gprime); 
    };
    double S_star = 0;
    if (fabs(g)>ACCURACY) { S_star = S_seed; } // did not converge
    else { S_star = Si; };
    double C=0;
    double c  = option_price_european_call_payout(S,X,r,b,sigma,time);
    if (S>=S_star) {
	C=S-X;
    } 
    else {
	double d1 = (log(S_star/X)+(b+0.5*sigma_sqr)*time)/(sigma*time_sqrt);
	double A2 =  (1.0-exp((b-r)*time)*N(d1))* (S_star/q2); 
	C=c+A2*pow((S/S_star),q2);
    };
    return max(C,c); // know value will never be less than BS value
};
