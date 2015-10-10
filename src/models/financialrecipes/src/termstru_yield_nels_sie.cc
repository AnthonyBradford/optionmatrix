#include <cmath>
using namespace std;

double term_structure_yield_nelson_siegel(const double& t,
					  const double& beta0, 
					  const double& beta1, 
					  const double& beta2,
					  const double& lambda) { 
   if (t==0.0) return beta0;
   double tl = t/lambda;
   double r = beta0 + (beta1+beta2) * ((1-exp(-tl))/tl) + beta2 * exp(-tl);  
   return r; 
}; 
