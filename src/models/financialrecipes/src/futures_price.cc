#include <cmath>
using namespace std;

double futures_price(const double& S,                     // current price  of underlying asset
		     const double& r,                     // risk free interest rate
		     const double& time_to_maturity) {
    return exp(r*time_to_maturity)*S;
};
