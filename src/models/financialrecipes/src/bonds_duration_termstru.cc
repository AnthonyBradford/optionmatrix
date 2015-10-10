#include "fin_recipes.h"

double bonds_duration(const vector<double>& cashflow_times,
		      const vector<double>& cashflow_amounts,
		      const term_structure_class& d ) {
    double S=0;
    double D1=0;
    for (unsigned i=0;i<cashflow_times.size();i++){
	S += cashflow_amounts[i] * d.d(cashflow_times[i]);
	D1 += cashflow_times[i] * cashflow_amounts[i] * d.d(cashflow_times[i]);
    };
    return D1/S;
};
