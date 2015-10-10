#include <algorithm>
using namespace std;

double payoff_call(const double& S, 
		   const double& K){
    return max(0.0,S-K); 
};

double payoff_put (const double& S, 
		   const double& K) { 
    return max(0.0,K-S); 
};
