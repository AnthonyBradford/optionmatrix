#include <cmath>
#include "fin_recipes.h"

double bonds_yield_to_maturity( const vector<double>& cashflow_times, 
				const vector<double>& cashflow_amounts,
				const double& bondprice) {
  const float ACCURACY = 1e-5;
  const int MAX_ITERATIONS = 200;
  double bot=0, top=1.0;
  while (bonds_price(cashflow_times, cashflow_amounts, top) > bondprice) {
    top = top*2;
  };
  double r = 0.5 * (top+bot);
  for (int i=0;i<MAX_ITERATIONS;i++){
    double diff = bonds_price(cashflow_times, cashflow_amounts,r) - bondprice;
    if (fabs(diff)<ACCURACY) return r;
    if (diff>0.0)  { bot=r;} 
    else           { top=r; };
    r = 0.5 * (top+bot);
  };
  return r;
};
