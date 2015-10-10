#include <cmath>
#include <vector>
using namespace std;

double term_structure_discount_factor_cubic_spline(const double& t,
						   const double& b1,
						   const double& c1,
						   const double& d1,
						   const vector<double>& f,
						   const vector<double>& knots){ 
    double d = 1.0 + b1*t + c1*(pow(t,2)) + d1*(pow(t,3)); 
    for (int i=0;i<knots.size();i++) { 
	if (t >= knots[i]) { d += f[i] * (pow((t-knots[i]),3)); } 
	else { break; }; 
    }; 
    return d;   
}; 
