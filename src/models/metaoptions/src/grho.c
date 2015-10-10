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

#include <math.h>
#include <assert.h>

#include "metaoptions.h"

/* Rho for the generalized Black and Scholes formula */
double rho(int fCall, double S, double X, double T, double r, double b, double v) 
{
	double result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	if(b == 0.0)
		result = -T * gbs(fCall, S, X, T, r, b, v);
    else {
		const double vst = v * sqrt(T);
		const double d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (vst);
		const double d2 = d1 - vst;

		if(fCall) 
			result = T * X * exp(-r * T) * cnd(d2);
		else 
			result = -T * X * exp(-r * T) * cnd(-d2);
	}

	return result;
}

extern double rho_call(double S, double X, double T, double r, double b, double v) 
{
	double result;
    
	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	if(b == 0.0)
		result = -T * gbs_call(S, X, T, r, b, v);
    else {
		const double vst = v * sqrt(T);
		const double d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / vst;
		const double d2 = d1 - vst;

		result = T * X * exp(-r * T) * cnd(d2);
	}

	return result;
}

extern double rho_put(double S, double X, double T, double r, double b, double v) 
{
	double result;
    
	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	if(b == 0.0)
		result = -T * gbs_put(S, X, T, r, b, v);
    else {
		const double vst = v * sqrt(T);
		const double d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / vst;
		const double d2 = d1 - vst;

		result = -T * X * exp(-r * T) * cnd(-d2);
	}

	return result;
}

#ifdef GRHO_CHECK

void check_RhoForEuroCall(void)
{
	double S = 72.0, X = 75.0, T = 1.0, r = 0.09, v = 0.19, b = 0.09;

	assert_equal(rho(1, S, X, T, r, b, v), 38.7325);
	assert_equal(rho_call(S, X, T, r, b, v), 38.7325);
}

int main(void)
{
	check_RhoForEuroCall();
	return 0;
}
#endif

