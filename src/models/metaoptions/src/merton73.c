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

/* Merton (1973) Options on stock indices, page 4. */
double merton73(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double q,
	double v) 
{
	double d1, d2, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

	d1 = (log(S / X) + (r - q + pow2(v) / 2.0) * T) / (v * sqrt(T));
	d2 = d1 - v * sqrt(T);

	if(fCall) {
	  result = S * exp(-q * T) * cnd(d1) - X * exp(-r * T) * cnd(d2);
	} else { 
	  result = X * exp(-r * T) * cnd(-d2) - S * exp(-q * T) * cnd(-d1);
	}

	assert(is_sane(result));
	return result;
}

#ifdef MERTON73_CHECK

void check_merton73(void)
{
	double S = 100, X = 95.0, T = 0.5, r = 0.10, q = 0.05, v = 0.20;
	double result, fasit_put = 2.4648;

	result = merton73(0, S, X, T, r, q, v);
	assert_equal(result, fasit_put);
}

int main(void)
{
	check_merton73();
	return 0;
}
#endif

