#include "fin_recipes.h"

double bonds_price(const vector<double>& cashflow_times,  
		   const vector<double>& cashflows,
		   const term_structure_class& d) { 
    double p = 0; 
    for (unsigned i=0;i<cashflow_times.size();i++) { 
	p += d.d(cashflow_times[i])*cashflows[i];
    };
    return p; 
}; 
