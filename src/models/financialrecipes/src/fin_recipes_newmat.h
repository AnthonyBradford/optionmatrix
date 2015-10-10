#include <newmat/newmat.h>
using namespace NEWMAT;

// basic calculations
double mv_calculate_mean     (const Matrix& e, const Matrix& w);
double mv_calculate_variance (const Matrix& V, const Matrix& w);
double mv_calculate_st_dev   (const Matrix& V, const Matrix& w);

// find portfolios
ReturnMatrix mv_calculate_portfolio_given_mean_unconstrained(const Matrix& e,
							     const Matrix& V, 
							     const double& r);

 
