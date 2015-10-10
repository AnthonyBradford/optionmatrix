#include "config.h"

#ifdef HAVE_NEWMAT_NEWMAT_H
 #include <newmat/newmat.h>
#endif

#ifdef HAVE_NEWMAT_NEWMAT_H

using namespace NEWMAT;

ReturnMatrix mv_calculate_portfolio_given_mean_unconstrained(const Matrix& e, 
							     const Matrix& V, 
							     const double& r){
    int no_assets=e.Nrows();
    Matrix ones = Matrix(no_assets,1); for (int i=0;i<no_assets;++i){ ones.element(i,0) = 1; };
    Matrix Vinv = V.i();  // inverse of V
    Matrix A = (ones.t()*Vinv*e);  double a = A.element(0,0);
    Matrix B = e.t()*Vinv*e;       double b = B.element(0,0);
    Matrix C = ones.t()*Vinv*ones; double c = C.element(0,0);
    double d = b*c - a*a;
    Matrix Vinv1=Vinv*ones; 
    Matrix Vinve=Vinv*e;
    Matrix g = (Vinv1*b - Vinve*a)*(1.0/d);
    Matrix h = (Vinve*c - Vinv1*a)*(1.0/d);
    Matrix w = g + h*r;
    w.Release();
    return w;
};

#endif
