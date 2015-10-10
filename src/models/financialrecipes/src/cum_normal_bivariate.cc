#include <cmath> // include the standard library mathematics functions
using namespace std; // which are in the standard namespace
#include <iostream>

double N(const double&); // define the univariate cumulative normal distribution as a separate function

#ifndef PI 
const double PI=3.141592653589793238462643;
#endif 

inline double f(const double& x, const double& y, 
		const double& aprime, const double& bprime,
		const double& rho) {
    double r = aprime*(2*x-aprime) + bprime*(2*y-bprime) + 2*rho*(x-aprime)*(y-bprime);
    return exp(r);
};

inline double sgn(const double& x) {  // sign function
    if (x>=0.0)  return 1.0;
    return -1.0;
};

double N(const double& a, const double& b, const double& rho) {
    if ( (a<=0.0) && (b<=0.0) && (rho<=0.0) ) { 
	double aprime = a/sqrt(2.0*(1.0-rho*rho));
	double bprime = b/sqrt(2.0*(1.0-rho*rho));
	double A[4]={0.3253030, 0.4211071, 0.1334425, 0.006374323}; 
	double B[4]={0.1337764, 0.6243247, 1.3425378, 2.2626645  };
	double sum = 0;
	for (int i=0;i<4;i++) {
	    for (int j=0; j<4; j++) {
		sum += A[i]*A[j]* f(B[i],B[j],aprime,bprime,rho);
	    };
	};
	sum = sum * ( sqrt(1.0-rho*rho)/PI);
	return sum;
    }
    else  if ( a * b * rho <= 0.0 ) {
	if ( ( a<=0.0 ) && ( b>=0.0 ) && (rho>=0.0) ) {
	    return N(a) - N(a, -b, -rho); 
	}
	else if ( (a>=0.0) && (b<=0.0) && (rho>=0.0) ) {
	    return N(b) - N(-a, b, -rho); 
	}
	else if ( (a>=0.0) && (b>=0.0) && (rho<=0.0) ) {
	    return N(a) + N(b) - 1.0 + N(-a, -b, rho); 
	};
    }
    else  if ( a * b * rho >= 0.0 ) {
	double denum = sqrt(a*a - 2*rho*a*b + b*b);
	double rho1 = ((rho * a - b) * sgn(a))/denum;
	double rho2 = ((rho * b - a) * sgn(b))/denum;
	double delta=(1.0-sgn(a)*sgn(b))/4.0;
	return N(a,0.0,rho1) + N(b,0.0,rho2) - delta;
    }
    else {
	cout << " unknown " << endl;
    }
    return -99.9; // should never get here, alternatively throw exception
};
