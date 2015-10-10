#include <cmath>
#include <vector>
using namespace std;
#include <iostream>
double cash_flow_pv_discrete(const vector<double>& cflow_times,
			     const vector<double>& cflow_amounts,
			     const double& r){
    double PV=0.0; 
    for (int t=0; t<cflow_times.size();t++) {
	PV += cflow_amounts[t]/pow(1.0+r,cflow_times[t]);
    };
    return PV;
};
