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

/* Theta for the generalized Black and Scholes formula */
double theta(int fCall, double S, double X, double T, double r, double b, double v) 
{
	double st, d1, d2, sbrt, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	st = sqrt(T);
    d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * st);
    d2 = d1 - v * st;
	sbrt= S * exp((b - r) * T);

    if(fCall) {
        result = -sbrt * normdist(d1) * v / (2.0 * st) 
			- (b - r) * sbrt * cnd(d1) 
			- r * X * exp(-r * T) * cnd(d2);
	}
    else {
        result = -sbrt * normdist(d1) * v / (2.0 * st) 
			+ (b - r) * sbrt * cnd(-d1) 
			+ r * X * exp(-r * T) * cnd(-d2);
	}
    
	return result;
}

extern double theta_call(double S, double X, double T, double r, double b, double v) 
{
	double st, d1, d2, sbrt, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	st = sqrt(T);
    d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * st);
    d2 = d1 - v * st;
	sbrt= S * exp((b - r) * T);

	result = -sbrt * normdist(d1) * v / (2.0 * st) 
		- (b - r) * sbrt * cnd(d1) 
		- r * X * exp(-r * T) * cnd(d2);
    
	return result;
}

extern double theta_put(double S, double X, double T, double r, double b, double v) 
{
	double st, d1, d2, sbrt;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	st = sqrt(T);
    d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / (v * st);
    d2 = d1 - v * st;
	sbrt= S * exp((b - r) * T);

	return -sbrt * normdist(d1) * v / (2.0 * st) 
		+ (b - r) * sbrt * cnd(-d1) 
		+ r * X * exp(-r * T) * cnd(-d2);
}

#ifdef GTHETA_CHECK

void check_theta(void)
{
	double S = 430, X = 405, T = 1.0/12, r = 0.07, v = 0.20, b = 0.02; /* Interest rate - dividend yield (0.05) */

	assert_equal(theta(0, S, X, T, r, b, v), -31.1924);
	assert_equal(theta_put(S, X, T, r, b, v), -31.1924);
}


int main(void)
{
	check_theta();
	return 0;
}

#endif

