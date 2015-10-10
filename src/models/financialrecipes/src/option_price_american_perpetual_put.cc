#include <cmath>
using namespace std;

double option_price_american_perpetual_put(const double& S,  // price of underlying
					   const double& K,  // strike price
					   const double& r,  // interest rate
					   const double& q,  // yield on underlying
					   const double& sigma){ // volatility
    double sigma_sqr=pow(sigma,2);
    double h2 = 0.5 - ((r-q)/sigma_sqr)-sqrt(pow(((r-q)/sigma_sqr-0.5),2)+2.0*r/sigma_sqr);
    double pric = (K/(1.0-h2))*pow(((h2-1.0)/h2)*(S/K),h2);
    return pric;
};
