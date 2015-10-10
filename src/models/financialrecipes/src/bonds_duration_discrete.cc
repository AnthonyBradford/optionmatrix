#include <cmath>
#include <vector>
using namespace std;

double bonds_duration_discrete(const vector<double>& times,
			       const vector<double>& cashflows,
			       const double& r) {
    double B=0;
    double D=0;
    for (int i=0;i<times.size();i++){
 	D += times[i] * cashflows[i] / pow(1+r,times[i]);
	B  += cashflows[i] / pow(1+r,times[i]);
    };
    return D/B;
};
