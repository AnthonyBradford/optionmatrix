#include "fin_recipes.h"

term_structure_class_svensson::term_structure_class_svensson( const double& b0, const double& b1, const double& b2, const double& b3,
							      const double& tau1, const double& tau2) {
    beta0_=b0; beta1_=b1; beta2_=b2; beta3_=b3; tau1_=tau1; tau2_=tau2;
};

double term_structure_class_svensson::r(const double& t) const {
    if (t<=0.0) return beta0_;
    return term_structure_yield_svensson(t,beta0_,beta1_,beta2_,beta3_,tau1_,tau2_);
};
