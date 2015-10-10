#include "fin_recipes.h"
 
double bonds_duration_macaulay(const vector<double>& cashflow_times,
			       const vector<double>& cashflows,
			       const double& bond_price) {
  double y = bonds_yield_to_maturity(cashflow_times, cashflows, bond_price);
  return bonds_duration(cashflow_times, cashflows, y); // use YTM in duration 
};
