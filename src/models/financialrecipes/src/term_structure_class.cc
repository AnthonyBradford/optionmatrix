#include "fin_recipes.h"

term_structure_class::~term_structure_class(){};

double term_structure_class::f(const double& t1, const double& t2) const{
   double d1 = d(t1);
   double d2 = d(t2);
   return term_structure_forward_rate_from_discount_factors(d1,d2,t2-t1);
};

double term_structure_class::r(const double& t) const{
    return term_structure_yield_from_discount_factor(d(t),t);
};

double term_structure_class::d(const double& t) const {
    return term_structure_discount_factor_from_yield(r(t),t);
};
