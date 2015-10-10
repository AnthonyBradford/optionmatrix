#include <cmath>
using namespace std;
#include "normdist.h" // normal distribution definitions

double 
option_price_asian_geometric_average_price_call(const double& S,
						const double& K,
						const double& r,
						const double& q,
						const double& sigma,
						const double& time){
    double sigma_sqr = pow(sigma,2);
    double adj_div_yield=0.5*(r+q+sigma_sqr/6.0);
    double adj_sigma=sigma/sqrt(3.0);
    double adj_sigma_sqr = pow(adj_sigma,2);
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K) + (r-adj_div_yield + 0.5*adj_sigma_sqr)*time)/(adj_sigma*time_sqrt);
    double d2 = d1-(adj_sigma*time_sqrt);
    double call_price = S * exp(-adj_div_yield*time)* N(d1) - K * exp(-r*time) * N(d2);
    return call_price;
};
