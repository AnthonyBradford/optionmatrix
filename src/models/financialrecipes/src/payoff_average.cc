#include <cmath>
#include <numeric>
#include <vector> 
using namespace std;

double payoff_arithmetric_average_call(const vector<double>& prices, const double& K) {
    double sum=accumulate(prices.begin(), prices.end(),0.0); 
    double avg = sum/prices.size();
    return max(0.0,avg-K);
};

double payoff_geometric_average_call(const vector<double>& prices, const double& K) {
    double logsum=log(prices[0]);
    for (unsigned i=1;i<prices.size();++i){ logsum+=log(prices[i]); };
    double avg = exp(logsum/prices.size());
    return max(0.0,avg-K);
};
