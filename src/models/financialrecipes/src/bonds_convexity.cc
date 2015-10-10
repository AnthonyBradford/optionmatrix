#include <cmath>
#include "fin_recipes.h"

double bonds_convexity(const vector<double>& times,   
		       const vector<double>& cashflows,
		       const double& r ) {
    double C=0;
    for (int i=0;i<times.size();i++){
	C += cashflows[i] * pow(times[i],2) * exp(-r*times[i]);
    };
    double B=bonds_price(times, cashflows,r);
    return C/B;
};
