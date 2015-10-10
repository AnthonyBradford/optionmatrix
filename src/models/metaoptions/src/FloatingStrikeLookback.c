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

#include "metaoptions.h"

/* Floating strike lookback options */
double FloatingStrikeLookback(
	int fCall,
	double S,
	double SMin,
	double SMax,
	double T,
	double r,
	double b,
	double v) 
{
	double sT, ebT, vv, vsT, m, a1, a2, result;

	assert_valid_price(S);
	assert_valid_time(T);

	sT = sqrt(T);
	ebT = exp(b * T);
	vv = v*v;
	vsT = v * sT;
    
    if(fCall) 
        m = SMin;
	else 
        m = SMax;
    
	a1 = (log(S / m) + (b + vv / 2.0) * T) / vsT;
	a2 = a1 - vsT;

    if(fCall) {
        result = S * exp((b - r) * T) * cnd(a1) - m * exp(-r * T) * cnd(a2) 
			+ exp(-r * T) * vv / (2.0 * b) * S 
			* (pow((S / m), (-2.0 * b / vv)) * cnd(-a1 + 2.0 * b / v * sT) - ebT * cnd(-a1));
    }
	else {
        result = m * exp(-r * T) * cnd(-a2) - S * exp((b - r) * T) * cnd(-a1) 
			+ exp(-r * T) * vv / (2.0 * b) * S 
			* (-pow((S / m), (-2.0 * b / vv)) * cnd(a1 - 2.0 * b / v * sT) + ebT * cnd(a1));
    }

	return result;
}

#ifdef FLOATINGSTRIKELOOKBACK_CHECK
#include  <stdlib.h>
#include <stdio.h>

static void check_FloatingStrikeLookback(void)
{
	double S = 120, Smin = 100.0, T = 0.5, r = 0.10, b = r - 0.06, v = 0.30;
	double result, fasit = 25.3533;

	result = FloatingStrikeLookback(1, S, Smin, Smin, T, r, b, v);
	assert_equal(result, fasit);
}


int main(void)
{
	check_FloatingStrikeLookback();
	return 0;
}
#endif


