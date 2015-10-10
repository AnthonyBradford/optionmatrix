#include <cmath>
#include "normdist.h"
#include "fin_recipes.h"

double bond_option_price_put_zero_vasicek(const double& X,  // exercise price
					  const double& r, // current interest rate
					  const double& option_time_to_maturity,
					  const double& bond_time_to_maturity,
					  const double& a,  // parameters
					  const double& b, 
					  const double& sigma) {  
    double s_t = bond_time_to_maturity;
    double T_t = option_time_to_maturity;
    double T_s = s_t-T_t;
    double v_t_T;
    double sigma_P;
    if (a==0.0) { 
	v_t_T = sigma * sqrt ( T_t ) ;
	sigma_P = sigma*T_s*sqrt(T_t); 
    }
    else {
	v_t_T = sqrt (sigma*sigma*(1-exp(-2*a*T_t))/(2*a));
	double B_T_s = (1-exp(-a*T_s))/a;
	sigma_P = v_t_T*B_T_s;
    };
    double h = (1.0/sigma_P) * log (term_structure_discount_factor_vasicek(s_t,r,a,b,sigma)/
				    (term_structure_discount_factor_vasicek(T_t,r,a,b,sigma)*X) )
	+ sigma_P/2.0;
    double p = term_structure_discount_factor_vasicek(T_t,r,a,b,sigma)*N(-h+sigma_P)
	-term_structure_discount_factor_vasicek(s_t,r,a,b,sigma)*N(-h);
    return p;
};
