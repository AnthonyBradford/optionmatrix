#ifdef HAVE_ITPP_ITBASE_H
 #include <itpp/itbase.h>
 using namespace itpp;
#endif

#ifdef HAVE_ITPP_ITBASE_H
double mv_calculate_mean(const vec& e, const vec& w);
double mv_calculate_variance(const mat& V, const vec& w);
double mv_calculate_st_dev(const mat& V, const vec& w);

mat mv_calculate_portfolio_given_mean_unconstrained(const vec& e,
						    const mat& V, 
						    const double& r);

double option_price_put_american_finite_diff_implicit_itpp(const double& S,
							   const double& K, 
							   const double& r,
							   const double& sigma,
							   const double& time, 
							   const int& no_S_steps,
							   const int& no_t_steps);

#endif
