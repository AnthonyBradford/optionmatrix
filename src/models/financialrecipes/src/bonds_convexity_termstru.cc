#include "fin_recipes.h"
#include <cmath>

double bonds_convexity(const vector<double>& cashflow_times,
		       const vector<double>& cashflow_amounts,
		       const term_structure_class& d ) {
    double B=0;
    double Cx=0;
    for (unsigned i=0;i<cashflow_times.size();i++){
	B += cashflow_amounts[i] * d.d(cashflow_times[i]);
	Cx += pow(cashflow_times[i],2) * cashflow_amounts[i] * d.d(cashflow_times[i]);
    };
    return Cx/B;
};
