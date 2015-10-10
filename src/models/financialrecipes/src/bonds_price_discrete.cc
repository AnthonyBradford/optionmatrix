#include <cmath>
#include <vector>
using namespace std;

double bonds_price_discrete(const vector<double>& times,
			    const vector<double>& cashflows,
			    const double& r) { 
    double p=0;
    for (int i=0;i<times.size();i++) { 
	p += cashflows[i]/(pow((1+r),times[i]));
    };
    return p; 
};
