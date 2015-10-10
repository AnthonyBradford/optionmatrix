#include "fin_recipes.h" 

term_structure_class_nelson_siegel::term_structure_class_nelson_siegel( const double& b0,
									const double& b1,
									const double& b2,
									const double& l) {
   beta0_=b0; beta1_=b1; beta2_=b2; lambda_=l;
};

double term_structure_class_nelson_siegel::r(const double& t) const {
   if (t<=0.0) return beta0_;
   return term_structure_yield_nelson_siegel(t,beta0_,beta1_,beta2_,lambda_);
};
