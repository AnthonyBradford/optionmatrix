

//////// term structure ////////////////////////////////////////////////////

double term_structure_discount_factor_estimated_cir(const double& t, const double& r, 
						    const double& phi1, const double& phi2, const double& phi3);

double term_structure_yield_bliss(const double& t,
				  const double& gamma0, const double& gamma1, const double& gamma2,
				  const double& lambda1, const double& lambda2);

///////////////////////////////////////////////////////////////////////////
// fixed income derivatives, 
// Black Scholes bond option

double bond_option_price_call_zero_black_scholes(const double& B, const double& X, const double& r, 
						 const double& sigma, const double& time);

double bond_option_price_put_zero_black_scholes(const double& B, const double& X, const double& r,
						const double& sigma, const double& time);

double bond_option_price_call_coupon_bond_black_scholes(const double& B, const double& X, const double& r, 
							const double& sigma, const double& time, 
							vector<double> coupon_times, 
							vector<double> coupon_amounts);

double bond_option_price_put_coupon_bond_black_scholes(const double& B, const double& X, const double& r,
						       const double& sigma, const double& time, 
						       vector<double> coupon_times,
						       vector<double> coupon_amounts);



/// Vasicek model, explicit call 

double bond_option_price_call_zero_vasicek(const double& X, // exercise price
					   const double& r, // current interest rate
					   const double& op);

