#include <cmath>
#include <vector>
using namespace std;

double bonds_price(const vector<double>& cashflow_times,
		   const vector<double>& cashflows,
		   const double& r) { 
    double p=0; 
    for (int i=0;i<cashflow_times.size();i++) { 
	p += exp(-r*cashflow_times[i])*cashflows[i];
    };
    return p; 
};
