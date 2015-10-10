#include <cmath>
using namespace std;

double term_structure_discount_factor_vasicek(const double& time,
					      const double& r,
					      const double& a,
					      const double& b, 
					      const double& sigma){
    double A,B;
    double sigma_sqr = sigma*sigma;
    double aa = a*a;
    if (a==0.0){
	B = time;
	A = exp(sigma_sqr*pow(time,3))/6.0;
    }
    else {
	B = (1.0 - exp(-a*time))/a;
	A = exp( ((B-time)*(aa*b-0.5*sigma_sqr))/aa -((sigma_sqr*B*B)/(4*a)));
    };
    double dfact = A*exp(-B*r);
    return dfact;
}
