#include "fin_recipes.h"

term_structure_class_vasicek::term_structure_class_vasicek(const double& r, const double& a,
							   const double& b, const double& sigma) {
    r_=r; a_=a; b_=b; sigma_=sigma;
};

double term_structure_class_vasicek::d(const double& T) const{
    return term_structure_discount_factor_vasicek(T,r_,a_,b_,sigma_);
};
