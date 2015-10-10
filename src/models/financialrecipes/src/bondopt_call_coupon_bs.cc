#include <cmath>
#include "normdist.h"
#include "fin_recipes.h"

double bond_option_price_call_coupon_bond_black_scholes( const double& B, 
							 const double& X, 
							 const double& r, 
							 const double& sigma,
							 const double& time, 
							 const vector<double> coupon_times, 
							 const vector<double> coupon_amounts){
    double adjusted_B=B;
    for (unsigned int i=0;i<coupon_times.size();i++) { // subtract present value of coupons
	if (coupon_times[i]<=time) { // coupon paid befor option expiry
	    adjusted_B -= coupon_amounts[i] * exp(-r*coupon_times[i]);
	};
    };
    return bond_option_price_call_zero_black_scholes(adjusted_B,X,r,sigma,time);
};
