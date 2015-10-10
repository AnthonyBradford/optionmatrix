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

#include <assert.h>
#include <stdlib.h>
#include <math.h>


/* European options */

/* Black and Scholes (1973) Stock options */
double blackscholes(int fCall, double S, double X, double T, double r, double v) 
{
	double vst, d1, d2;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

	assert(r >= 0.0);			/* Interest rate >= 0.0 */
	assert(v > 0.0 && v <= 100.0);	/* Volatility between 0 and 100 */
    
	vst = v * sqrt(T);
    d1 = (log(S / X) + (r + pow2(v) / 2.0) * T) / (vst);
    d2 = d1 - vst;
    if(fCall) 
        return S * cnd(d1) - X * exp(-r * T) * cnd(d2);
    else 
        return X * exp(-r * T) * cnd(-d2) - S * cnd(-d1);
}

extern double blackscholes_put(double S, double X, double T, double r, double v) 
{
	double vst, d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
    d1 = (log(S / X) + (r + pow2(v) / 2) * T) / (vst);
	return X * exp(-r * T) * cnd(-(d1 - vst)) - S * cnd(-d1);
}

extern double blackscholes_call(double S, double X, double T, double r, double v) 
{
	double vst, d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
    d1 = (log(S / X) + (r + pow2(v) / 2) * T) / (vst);

	return S * cnd(d1) - X * exp(-r * T) * cnd((d1 - vst));
}

#ifdef BLACKSCHOLES_CHECK

void check_blackscholes(void)
{
	double S = 60.0, X = 65.0, T = 0.25, r = 0.08, v = 0.30;

	assert_equal(blackscholes(1, S, X, T, r, v), 2.1334);
	assert_equal(blackscholes_call(S, X, T, r, v), 2.1334);

	S = 96.1469; X = 90.0; T = 0.75; r = 0.10; v = 0.25;
	assert_equal(blackscholes(1, S, X, T, r, v), 15.6465);
	assert_equal(blackscholes_call(S, X, T, r, v), 15.6465);
}


int main(void)
{
	check_blackscholes();
	return 0;
}
#endif

