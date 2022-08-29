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

#include "metaoptions.h"

#include <math.h>
#include <assert.h>


/* Black (1977) Options on futures/forwards */
double black76(int fCall, double F, double X, double T, double r, double v) 
{
	double vst, d1, d2, result;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
	d1 = (log(F / X) + (pow2(v) / 2.0) * T) / vst;
	d2 = d1 - vst;

	if(fCall) {
		result = exp(-r * T) * (F * cnd(d1) - X * cnd(d2));
	} else {
		result = exp(-r * T) * (X * cnd(-d2) - F * cnd(-d1));
	}

	assert(is_sane(result));
	return result;
}

extern double black76_put(double F, double X, double T, double r, double v) 
{
	double vst, d1;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
	d1 = (log(F / X) + (pow2(v) / 2) * T) / vst;

	return exp(-r * T) * (X * cnd(-(d1 - vst)) - F * cnd(-d1));
}


extern double black76_call(double F, double X, double T, double r, double v) 
{
	double vst, d1;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
	d1 = (log(F / X) + (pow2(v) / 2) * T) / vst;

	return exp(-r * T) * (F * cnd(d1) - X * cnd((d1 - vst)));
}

#ifdef BLACK76_CHECK

void check_black76(void)
{
	double T = 3.0/12.0, S = 70.0, X = 70.0, r = 0.05, v = 0.28;
	double result, fasit_put = 1.7011, fasit_call = 1.7011;

	assert_equal(black76(0, S, X, T, r, v), 3.8579);
	assert_equal(black76_put(S, X, T, r, v), 3.8579);

	S = 19; X = 19; T = 0.75; r = 0.10, v = 0.28; /* Page 5 */

	result = black76(0, S, X, T, r, v);
	assert_equal(result, fasit_put);

	result = black76(1, S, X, T, r, v);
	assert_equal(result, fasit_call);
}

int main(void)
{
	check_black76();
	return 0;
}

#endif

