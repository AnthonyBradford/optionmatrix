#include <iostream>

#include "config.h"
#include "fin_recipes.h"
#include "prototypes.h"

#ifdef HAVE_NEWMAT_NEWMAT_H
 #include "fin_recipes_newmat.h"
#endif 

#ifdef HAVE_ITPP_ITBASE_H
 #include "fin_recipes_itpp.h"
#endif 

#ifdef HAVE_LIBGSL
 #include "fin_recipes_gsl.h"
#endif

using namespace std;

int main() {
    present_value_examples();
    bond_pricing_flat_term_structure_examples();
    term_structure_examples();
    forwards_futures_examples();
    binomial_examples();
    black_scholes_examples();
    black_scholes_extensions_examples();
    binomial_approximations_examples();
    warrant_examples();
    simulation_examples();
    finite_differences_examples();
    approximations_examples(); 
    alternative_formulas_examples();
    average_and_lookback_options_examples();
    examples_generic_binomial();
    examples_trinomial_trees();
    bond_options_examples();
    credit_risk_examples();
    term_structure_model_examples();
    binomial_term_structure_models_examples();
    examples_interest_rate_trees_gbm(); 
    examples_interest_rate_trees_ho_lee();
    term_structure_derivatives_examples();
    normal_distribution_examples();

#ifdef HAVE_NEWMAT_NEWMAT_H
    examples_mean_variance_newmat();
    examples_finite_diffs_using_newmat();
#else
    std::cout << "\nNEWMAT library needed for:\nexamples_mean_variance_newmat();\nexamples_finite_diffs_using_newmat();\n";
#endif

#ifdef HAVE_ITPP_ITBASE_H
    examples_mean_variance_itpp();
    examples_finite_diffs_using_itpp();
#else
    std::cout << "\nITPP library needed for:\nexamples_mean_variance_itpp();\nexamples_finite_diffs_using_itpp();\n";
#endif
};
