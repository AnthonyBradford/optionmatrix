#include "fin_recipes.h"

term_structure_class_cubic_spline::
term_structure_class_cubic_spline ( const double& b, const double& c, const double& d, 
				    const vector<double>& f, const vector<double>& knots) {
    b_ = b;    c_ = c;    d_ = d;   f_.clear();  knots_.clear();
    if (f.size()!=knots.size()){ return; };
    for (int i=0;i<f.size();++i) { 
	f_.push_back(f[i]);
	knots_.push_back(knots[i]);
    };
};

double term_structure_class_cubic_spline::d(const double& T) const {
   return term_structure_discount_factor_cubic_spline(T,b_,c_,d_,f_,knots_);
};
