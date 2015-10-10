#include <cmath>
using namespace std;

#include "fin_recipes.h"

double bonds_yield_to_maturity_discrete( const vector<double>& times, 
					 const vector<double>& cashflows,
					 const double& bondprice) {
    const double ACCURACY = 1e-5;
    const int MAX_ITERATIONS = 200;
    double bot=0, top=1.0;
    while (bonds_price_discrete(times, cashflows, top) > bondprice) { top = top*2; };
    double r = 0.5 * (top+bot);
    for (int i=0;i<MAX_ITERATIONS;i++){
	double diff = bonds_price_discrete(times, cashflows,r) - bondprice;
	if (fabs(diff)<ACCURACY) return r;
	if (diff>0.0)  { bot=r;} 
	else           { top=r; };
	r = 0.5 * (top+bot);
    };
    return r;
};
