#include "fin_recipes.h"
//#include "term_structure_class_ho_lee.h"

inline double hT(const double& T, const double& delta, const double& pi){
    return (1.0/(pi+(1-pi)*pow(delta,T)));
};

double term_structure_class_ho_lee::d(const double& T) const{
    double d=(*initial_term_).d(T+n_)/(*initial_term_).d(n_);
    for (int j=1;j<n_;++j){
	d *=  hT(T+(n_-j),delta_,pi_) / hT(n_-j,delta_,pi_) ;
    };
    d *= hT(T,delta_,pi_)*pow(delta_,T*(n_-i_));
    return d;
};
