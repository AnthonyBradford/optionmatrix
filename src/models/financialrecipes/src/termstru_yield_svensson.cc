#include <cmath>
using namespace std;

double term_structure_yield_svensson(const double& t, 
				     const double& beta0, 
				     const double& beta1, 
				     const double& beta2, 
				     const double& beta3,
				     const double& tau1, 
				     const double& tau2){
   if (t==0.0) return beta0;
   double r = beta0;
   r += beta1* ((1-exp(-t/tau1))/(t/tau1)) ;
   r += beta2 * ( ((1-exp(-t/tau1))/(t/tau1)) - exp(-t/tau1) );
   r += beta3 * ( ((1-exp(-t/tau2))/(t/tau2)) - exp(-t/tau2) );
   return r; 
}; 
