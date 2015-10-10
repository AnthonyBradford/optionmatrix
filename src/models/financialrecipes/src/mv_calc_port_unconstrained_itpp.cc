#include "config.h"

#ifdef HAVE_ITPP_ITBASE_H
 #include <itpp/itbase.h>
 using namespace itpp;
#endif

#ifdef HAVE_ITPP_ITBASE_H

mat mv_calculate_portfolio_given_mean_unconstrained(const vec& e, 
						    const mat& V, 
						    const double& r){
    int no_assets=e.size();
    vec one = ones(no_assets);
    mat Vinv = inv(V);               // inverse of V
    mat A = one.transpose()*Vinv*e;
    double a = A(0,0);
    mat B = e.transpose()*Vinv*e;      
    double b = B(0,0);
    mat C = one.transpose()*Vinv*one;  
    double c = C(0,0);
    double d = b*c-a*a;
    mat Vinv1=Vinv*one; 
    mat Vinve=Vinv*e;
    mat g = (Vinv1*b - Vinve*a)*(1.0/d);
    mat h = (Vinve*c - Vinv1*a)*(1.0/d);
    mat w = g + h*r;
    return w;
};

#endif
