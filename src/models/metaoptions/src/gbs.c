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

double gbs(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v) 
{
	double vst, d1, d2, ebrt, ert, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
	assert(is_sane(vst));
	d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / vst;
	d2 = d1 - vst;
	ebrt = exp((b - r) * T);
	ert = exp(-r * T);

	if(fCall) {
		result = S * ebrt * cnd(d1) - X * ert  * cnd(d2);
	} else {
		result = X * ert  * cnd(-d2) - S * ebrt * cnd(-d1);
	}

	assert(is_sane(result));
	return result;
}

extern double gbs_call(double S, double X, double T, double r, double b, double v) 
{
	double vst, d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
	d1 = (log(S / X) + (b + pow2(v) / 2) * T) / vst;

	return S * exp((b - r) * T) * cnd(d1) - X * exp(-r * T)  * cnd(d1 - vst);
}

extern double gbs_put(double S, double X, double T, double r, double b, double v) 
{
	double vst, d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
	d1 = (log(S / X) + (b + pow2(v) / 2) * T) / vst;

	return X * exp(-r * T)  * cnd(-(d1 - vst)) - S * exp((b - r) * T) * cnd(-d1);
}

#ifdef GBS_CHECK

void check_gbs(void)
{
	double S = 75.0, X = 70.0, T = 0.5, r = 0.10, b = 0.05, v = 0.35;
	
	assert_equal(gbs(0, S, X, T, r, b, v), 4.0870);
	assert_equal(gbs_put(S, X, T, r, b, v), 4.0870);
}

int main(void)
{
	check_gbs();
	return 0;
}
#endif

