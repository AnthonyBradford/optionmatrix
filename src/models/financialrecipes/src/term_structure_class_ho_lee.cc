#include "fin_recipes.h"

term_structure_class_ho_lee::term_structure_class_ho_lee(term_structure_class* fitted_term,
							 const int & n, 
							 const int & i, 
							 const double& delta, 
							 const double& pi){
    initial_term_=fitted_term;
    n_=n;
    i_=i;
    delta_=delta;
    pi_=pi;
};
