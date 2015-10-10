#include <cmath>
using namespace std;

double option_price_american_perpetual_call(const double& S,
					    const double& K, 
					    const double& r,
					    const double& q,
					    const double& sigma){
    double sigma_sqr=pow(sigma,2);
    double h1 = 0.5 - ((r-q)/sigma_sqr); 
    h1 += sqrt(pow(((r-q)/sigma_sqr-0.5),2)+2.0*r/sigma_sqr);
    double pric=(K/(h1-1.0))*pow(((h1-1.0)/h1)*(S/K),h1);
    return pric;
};
