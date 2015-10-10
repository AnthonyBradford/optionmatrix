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

/* European currency options, page 6 in da book */
extern double GarmanKohlhagen(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double rf,
	double v)
{
	double d1, d2, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_interest_rate(rf);
	assert_valid_volatility(v);

	d1 = (log(S/X) + (r-rf+pow(v, 2.0)/2.0)*T) / (v * sqrt(T));
	d2 = d1 - (v * sqrt(T));

	if(fCall) 
		result 
			= (S * exp(-rf* T) * cnd(d1))
			- (X * exp(-r * T) * cnd(d2));
	else
		result
			= (X * exp(-r * T) * cnd(-d2))
			- (S * exp(-rf* T) * cnd(-d1));

	return result;
}

#ifdef GARMANKOHLHAGEN_CHECK

#include <stdio.h>

int main(void)
{
	double S = 1.56, X = 1.60, T = 0.5, r = 0.06, rf = 0.08, v = 0.12;
	double result, fasit = 0.0291;

	result = GarmanKohlhagen(1, S, X, T, r, rf, v);
	assert_equal(result, fasit);
	return 0;
}
#endif




