#include <cmath>
using namespace std;

double term_structure_discount_factor_cir(const double& t,
					  const double& r,
					  const double& kappa,
					  const double& lambda,
					  const double& theta,
					  const double& sigma){
    double sigma_sqr=pow(sigma,2);
    double gamma = sqrt(pow((kappa+lambda),2)+2.0*sigma_sqr);
    double denum = (gamma+kappa+lambda)*(exp(gamma*t)-1)+2*gamma;
    double p=2*kappa*theta/sigma_sqr;
    double enum1= 2*gamma*exp(0.5*(kappa+lambda+gamma)*t);
    double A = pow((enum1/denum),p);
    double B = (2*(exp(gamma*t)-1))/denum;
    double dfact=A*exp(-B*r);
    return dfact;
};
