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

/* Supershare options */
double SuperShare(double S, double XL, double XH, double T, double r, double b, double v) 
{
	double d1, d2, result;

	assert_valid_price(S);
	assert_valid_strike(XL);
	assert_valid_strike(XH);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    d1 = (log(S / XL) + (b + pow2(v) / 2.0) * T) / (v * sqrt(T));
    d2 = (log(S / XH) + (b + pow2(v) / 2.0) * T) / (v * sqrt(T));

    result =  S * exp((b - r) * T) / XL * (cnd(d1) - cnd(d2));

	assert(is_sane(result));
	return result;
}

#ifdef SUPERSHARE_CHECK

void check_SuperShare(void)
{
	double S = 100, XL = 90, XH = 110.0, T = 0.25, v = 0.20, r = 0.10, b = 0.0;
	double fasit = 0.7389;

	double computed = SuperShare(S, XL, XH, T, r, b, v);
	assert_equal(fasit, computed);
}

int main(void)
{
	check_SuperShare();
	return 0;
}

#endif

