#include <cmath>
using namespace std;
#include "normdist.h"

double simulate_lognormal_random_variable(const double& S,  // current value of variable
					  const double& r,  // interest rate
					  const double& sigma,  // volatitily 
					  const double& time) {  // time to final date
   double R = (r - 0.5 * pow(sigma,2) )*time;
   double SD = sigma * sqrt(time);
   return S * exp(R + SD * random_normal());
};
