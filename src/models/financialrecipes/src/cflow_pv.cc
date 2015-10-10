#include <cmath>
#include <vector>
using namespace std;

double cash_flow_pv( const vector<double>& cflow_times, 
		     const vector<double>& cflow_amounts,
		     const double& r){
    double PV=0.0;
    for (int t=0; t<cflow_times.size();t++) {
	PV += cflow_amounts[t] * exp(-r*cflow_times[t]);
    };
    return PV;
};
