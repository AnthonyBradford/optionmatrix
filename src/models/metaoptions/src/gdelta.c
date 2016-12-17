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

double delta(int fCall, double S, double X, double T, double r,  double b, double v) 
{
	double d1, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    d1 = (log(S / X) + (b + pow(v, 2.0) / 2.0) * T) / (v * sqrt(T));
	result = exp((b - r) * T);
    
    if(fCall)
        result *= cnd(d1);
    else 
        result *= (cnd(d1) - 1.0);
    
    return result;
}

extern double delta_call(double S, double X, double T, double r,  double b, double v) 
{
	double d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * sqrt(T));
	return exp((b - r) * T) * cnd(d1);
}

extern double delta_put(double S, double X, double T, double r,  double b, double v) 
{
	double d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * sqrt(T));
	return exp((b - r) * T) * (cnd(d1) - 1.0);
}
#ifdef GDELTA_CHECK

void check_delta(void)
{
	/* Delta. Check both put and call */
	double X = 100, S = 105, r = 0.10, v = 0.36, b = 0.0, T = 0.5;

	assert_equal(delta(1, S, X, T, r, b, v), 0.5946);
	assert_equal(delta(0, S, X, T, r, b, v), -0.3566);

	/* Inline versions */
	assert_equal(delta_call(S, X, T, r, b, v), 0.5946);
	assert_equal(delta_put(S, X, T, r, b, v), -0.3566);

	S = 10, X = 100, T = 0.75, r = 0.04, b = 0.04, v = 0.2;
	assert_equal(delta_put(S, X, T, r, b, v), -1.0);
}

int main(void)
{
	check_delta();
	return 0;
}

#endif

