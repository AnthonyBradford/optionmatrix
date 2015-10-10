#include <cmath>
#include <vector>
using namespace std;

double bonds_duration(const vector<double>& cashflow_times,
		      const vector<double>& cashflows,
		      const double& r) {
    double S=0;
    double D1=0;
    for (int i=0;i<cashflow_times.size();i++){
	S  +=                     cashflows[i] * exp(-r*cashflow_times[i]);
 	D1 += cashflow_times[i] * cashflows[i] * exp(-r*cashflow_times[i]);
    };
    return D1 / S;
};
