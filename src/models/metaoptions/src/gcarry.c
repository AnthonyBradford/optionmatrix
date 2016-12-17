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


/* Carry for the generalized Black and Scholes formula */
double carry(int fCall, double S, double X, double T, double r, double b, double v) 
{
	double d1, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);

	assert(r >= 0.0);			/* Interest rate >= 0.0 */
	assert(b >= 0.0);			/* cost of carry >= 0.0 */
	assert(v > 0.0 && v <= 100.0);	/* Volatility between 0 and 100 */
    
    d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * sqrt(T));

    if(fCall)
        result = T * S * exp((b - r) * T) * cnd(d1);
    else 
        result = -T * S * exp((b - r) * T) * cnd(-d1);
    
    return result;
}

extern double carry_call(double S, double X, double T, double r, double b, double v) 
{
	double d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * sqrt(T));
	return T * S * exp((b - r) * T) * cnd(d1);
}

extern double carry_put(double S, double X, double T, double r, double b, double v) 
{
	double d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * sqrt(T));
	return -T * S * exp((b - r) * T) * cnd(-d1);
}

#ifdef GCARRY_CHECK

void check_carry(void)
{
	/* Check cost of carry for a put  */
	double S = 500.0, X = 490.0, r = 0.08, b = 0.03, v = 0.15, T = 3.0/12;

	assert_equal(carry(0, S, X, T, r, b, v), -42.2254);
	assert_equal(carry_put(S, X, T, r, b, v), -42.2254);
}

int main(void)
{
	check_carry();
	return 0;
}

#endif

