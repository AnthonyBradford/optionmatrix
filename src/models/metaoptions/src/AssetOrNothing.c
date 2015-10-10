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

/*
 * Performance notes:
 * Calls/sec	Action
 * 2.750.000	Creating 2 exit points instead of just one.
 * 2.750.000	Calling inline functions instead
 * 4.098.000	Nice ;-)
 */

/* Asset-or-nothing options */
double AssetOrNothing(int fCall, double S, double X, double T, double r, double b, double v) 
{
	double d, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    d = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * sqrt(T));
	result = S * exp((b - r) * T);

    if(fCall) 
		result *= cnd(d);
	else
		result *= cnd(-d);

	return result;
}

extern double AssetOrNothing_put(double S, double X, double T, double r, double b, double v) 
{
	double d;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    d = (log(S / X) + (b + pow2(v) / 2) * T) / (v * sqrt(T));
	return S * exp((b - r) * T) * cnd(-d);
}

extern double AssetOrNothing_call(double S, double X, double T, double r, double b, double v) 
{
	double d;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    d = (log(S / X) + (b + pow2(v) / 2) * T) / (v * sqrt(T));
	return S * exp((b - r) * T) * cnd(d);
}

#ifdef ASSETORNOTHING_CHECK
void check_AssetOrNothing(void)
{
	double S = 70.0, X = 65.0, T = 0.5, r = 0.07, b = 0.07 - 0.05, v = 0.27;
	double answer = 20.2069;

	double computed = AssetOrNothing(0, S, X, T, r, b, v);
	assert_equal(computed, answer);
	assert_equal(computed, AssetOrNothing_put(S, X, T, r, b, v));
}


int main(void)
{
	check_AssetOrNothing();
	printf("Mangler data for calls\n");
	return 0;
}
#endif

