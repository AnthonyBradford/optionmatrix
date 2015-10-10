#include <cmath>
#include "fin_recipes.h"

double bonds_convexity_discrete(const vector<double>& times,
				const vector<double>& cashflows,
				const double& r) {
    double Cx=0;
    for (int i=0;i<times.size();i++){
	Cx+= cashflows[i]*times[i]*(times[i]+1)/(pow((1+r),times[i]));
    };
    double B=bonds_price_discrete(times, cashflows, r);
    return (Cx/(pow(1+r,2)))/B;
};
