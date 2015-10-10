/*
    libmetaoptions - A collection of option-related functions. 
    Copyright (C) 2000-2004 B. Augestad, bjorn.augestad@gmail.com 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdlib.h>
#include <math.h>

#include "metaoptions.h"

/* Payoff function used in three dimensional binomial tree */
static double PayoffFunction(
	int type,
	int fCall,
	double S1,
	double S2,
	double Q1,
	double Q2,
	double X1,
	double X2)
{
	double z, qs1, qs2, result;

	assert(type >= TDB_OPTIONTYPE_MIN);
	assert(type <= TDB_OPTIONTYPE_MAX);

	if(fCall)
		z = 1.0;
	else
		z = -1.0;

	qs1 = Q1 * S1;
	qs2 = Q2 * S2;
	switch(type) {
		case TDB_SPREAD_OPTION:
			result = z * (qs1 - qs2) - z * X1;
			break;
	
		case TDB_OPTION_ON_THE_MAX:
			result = z * fmax(qs1, qs2) - z * X1;
			break;
	
		case TDB_OPTION_ON_THE_MIN:
			result = z * fmin(qs1, qs2) - z * X1;
			break;
	
		case TDB_DUAL_STRIKE_OPTION:
			result = fmax(z * (qs1 - X1), z * (qs2 - X2));
			break;
	
		case TDB_REVERSE_DUAL_STRIKE_OPTION:
			result = fmax(z * (qs1 - X1), z * (X2 - qs2));
			break;
	
		case TDB_PORTFOLIO_OPTION:
			result = z * (qs1 + qs2) - z * X1;
			break;
	
		case TDB_EXCHANGE_OPTION:
			result = qs1 - qs2;
			break;
	
		default:
			abort();
	}

	result = fmax(0.0, result);
	return result;
}


/* Three dimensional binomial tree */
extern double ThreeDimensionalBinomial(
	int type,
	int EuropeanOption,
	int fCall,
	double S1,
	double S2,
	double Q1,
	double Q2,
	double X1,
	double X2,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double rho_,
	int n)
{
	double result, dt, sdt, mu1, mu2, u, d;
	int i, j, m;
	double optval[n + 1][n + 1];

	assert_valid_price(S1);
	assert_valid_price(S2);
	assert_valid_strike(X1);
	assert_valid_strike(X2);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b1);
	assert_valid_cost_of_carry(b2);
	assert_valid_volatility(v1);
	assert_valid_volatility(v2);

	assert(n > 0);
	assert(type >= TDB_OPTIONTYPE_MIN);
	assert(type <= TDB_OPTIONTYPE_MAX);


	dt = T / n;
	sdt = sqrt(dt);
	mu1 = b1 - pow2(v1) / 2.0;
	mu2 = b2 - pow2(v2) / 2.0;
	u = exp(mu1 * dt + v1 * sdt);
	d = exp(mu1 * dt - v1 * sdt);

	for(j = 0; j <= n; j++) {
		const double Y1 = (2.0 * j - n) * sdt;
		const double NodeValueS1 = S1 * pow(u, (double)j) * pow(d, (double)(n - j));

		for(i = 0; i <= n; i++) {
			double NodeValueS2;
			const double y2 = rho_ * Y1 + sqrt(1.0 - pow2(rho_)) * (2.0 * i - n) * sdt;
			(void)y2; /* Read TODO file for more info */

			NodeValueS2 
				= S2 * exp(mu2 * n * dt) 
				* exp(v2 * (rho_ * Y1 + sqrt(1 - pow2(rho_)) 
				* (2.0 * i - n) * sdt));

			optval[j][i] = PayoffFunction(type, fCall, NodeValueS1, NodeValueS2, Q1, Q2, X1, X2);
		} 
	}


	for(m = n - 1; m >= 0; m--) {
		for(j = 0; j <= m; j++) {
			const double Y1 = (2.0 * j - m) * sdt;
			const double NodeValueS1 = S1 * pow(u, (double)j) * pow(d, (double)(m - j));

			for(i = 0; i <= m; i++) {
				const double y2 = rho_ * Y1 + sqrt(1.0 - pow2(rho_)) * (2.0 * i - m) * sdt;
				const double NodeValueS2 = S2 * exp(mu2 * m * dt) * exp(v2 * y2);
				optval[j][i] 
					= 0.25 * (
						  optval[j][i] 
						+ optval[j + 1][i] 
						+ optval[j][i + 1]  
						+ optval[j + 1][i + 1]
					) * exp(-r * dt);

				if(!EuropeanOption) {
					optval[j][i] = fmax(optval[j][i], PayoffFunction(type, fCall, NodeValueS1, NodeValueS2, Q1, Q2, X1, X2));
				}
			} 
		}

	}

	result = optval[0][0];
	assert(is_sane(result));
	return result;
}

