#include <cmath>
#include <vector>
using namespace std;

double bonds_price(const vector<double>& coupon_times,
		   const vector<double>& coupon_amounts,
		   const vector<double>& principal_times,
		   const vector<double>& principal_amounts, 
		   const double& r) { 
    double p = 0; 
    for (int i=0;i<coupon_times.size();i++) { 
	p += exp(-r*coupon_times[i])*coupon_amounts[i];
    };
    for (int i=0;i<principal_times.size();i++) { 
	p += exp(-r*principal_times[i])*principal_amounts[i]; 
    }; 
    return p; 
};
