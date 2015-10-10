#include "fin_recipes.h"
 
double bonds_duration_macaulay_discrete(const vector<double>& times,
					const vector<double>& cashflows,
					const double& bond_price) {
  double y = bonds_yield_to_maturity_discrete(times, cashflows, bond_price);
  return bonds_duration_discrete(times, cashflows, y); // use YTM in duration calculation
};
