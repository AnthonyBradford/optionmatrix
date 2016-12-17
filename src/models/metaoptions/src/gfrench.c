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


/* French (1984) adjusted Black and Scholes model for trading day volatility */
double french(int fCall, double S, double X, double T, double t1, double r, double b, double v) 
{
	double vst1, d1, d2, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);

	assert(r >= 0.0);			/* Interest rate >= 0.0 */
	assert(b >= 0.0);			/* cost of carry >= 0.0 */
	assert(v > 0.0 && v <= 100.0);	/* Volatility between 0 and 100 */
    
	vst1 = v*sqrt(t1);
    d1 = (log(S / X) + b * T + pow2(v) / 2.0 * t1) / vst1;
    d2 = d1 - vst1;

    if(fCall)
        result = S * exp((b - r) * T) * cnd(d1) - X * exp(-r * T) * cnd(d2);
    else 
        result = X * exp(-r * T) * cnd(-d2) - S * exp((b - r) * T) * cnd(-d1);
    
    return result;
}

extern double french_put(double S, double X, double T, double t1, double r, double b, double v) 
{
	double vst1, d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	vst1 = v * sqrt(t1);
    d1 = (log(S / X) + b * T + pow2(v) / 2.0 * t1) / vst1;
  
	return X * exp(-r * T) * cnd(-(d1 - vst1)) - S * exp((b - r) * T) * cnd(-d1);
}

extern double french_call(double S, double X, double T, double t1, double r, double b, double v) 
{
	double vst1, d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	vst1 = v * sqrt(t1);
    d1 = (log(S / X) + b * T + pow2(v) / 2.0 * t1) / vst1;
  
	return S * exp((b - r) * T) * cnd(d1) - X * exp(-r * T) * cnd(d1 - vst1);
}

#ifdef GFRENCH_CHECK

void check_french(void)
{
	double S = 70, X = 75.0, T = 0.4, t1 = 0.4111, r = 0.08, b = 0.08, v = 0.30;
	double fasit = 6.8836;

	double result = french(0, S, X, T, t1, r, b, v);
	assert_equal(result, fasit);
}

int main(void)
{
	check_french();
	return 0;
}
#endif

