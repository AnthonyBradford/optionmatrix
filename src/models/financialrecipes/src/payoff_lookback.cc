#include <vector>
#include <algorithm>
using namespace std;

double payoff_lookback_call(const vector<double>& prices, const double& unused_variable) {
   double m = *min_element(prices.begin(),prices.end()); 
   return prices.back()-m; // always positive or zero
};

double payoff_lookback_put(const vector<double>& prices, const double& unused_variable) {
    double m = *max_element(prices.begin(),prices.end());
    return m-prices.back(); // max is always larger or equal.
};

