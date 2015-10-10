#include "fin_recipes.h"

//term_structure_class_cir::~term_structure_class_cir(){;};

term_structure_class_cir::term_structure_class_cir(const double& r, const double& k, const double& l,
						   const double& th, const double& sigma) {
    r_=r;  kappa_=k; lambda_=l; theta_=th; sigma_=sigma;
};

double term_structure_class_cir::d(const double& T) const{
    return term_structure_discount_factor_cir(T,r_,kappa_,lambda_,theta_,sigma_);
};
