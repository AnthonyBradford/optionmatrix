#include "config.h"

#include <cmath>
#include <iostream>
using namespace std;

#ifdef HAVE_LIBGSL
 #include "gsl/gsl_integration.h"
#endif 

#include "normdist.h"

#ifdef HAVE_LIBGSL

struct n3_parms {double h; double k; double rho12; double rho13; double rho23; };

extern "C"{
double f3(double z, void *p){
    struct n3_parms* parms = (struct n3_parms*)p;
    double h = (parms->h);
    double k = (parms->k);;
    double rho12 = (parms->rho12);
    double rho13 = (parms->rho13);
    double rho23 = (parms->rho23);
    double f = n(z);
    f*=N( (k-rho23*z)/sqrt(1.0-rho23*rho23),
	  (h-rho13*z)/(sqrt(1.0-rho13*rho13)),
	  (rho12-rho13*rho23)/(sqrt(1.0-rho13*rho13)*sqrt(1.0-rho23*rho23)));
    return f;
};
};

double N3(const double& h, const double& k, const double& j, 
	  const double& rho12, const double& rho13, const double& rho23){
    struct n3_parms parms = { h, k, rho12, rho13, rho23};
    size_t n=1000;
    gsl_integration_workspace* w = gsl_integration_workspace_alloc(n);
    gsl_function F;
    F.function = &f3;
    F.params=&parms;
    double result, error;
    gsl_integration_qags(&F,-20.0,j,1e-7,1e-7,n,w,&result,&error);
    gsl_integration_workspace_free(w);
    return result;
};

#endif
