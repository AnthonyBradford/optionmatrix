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

/* Gap options */
double GapOption(
	int fCall,
	double S,
	double X1,
	double X2,
	double T,
	double r,
	double b,
	double v) 
{
	double vsqrtT, d1, d2, result;

	assert_valid_price(S);
	assert_valid_strike(X1);
	assert_valid_strike(X2);
	assert_valid_time(T);

	vsqrtT = v * sqrt(T);
    d1 = (log(S / X1) + (b + pow2(v) / 2.0) * T) / vsqrtT;
    d2 = d1 - vsqrtT;

    if(fCall)
        result = S * exp((b - r) * T) * cnd(d1) - X2 * exp(-r * T) * cnd(d2);
	else 
        result = X2 * exp(-r * T) * cnd(-d2) - S * exp((b - r) * T) * cnd(-d1);

	return result;
}

#ifdef GAPOPTION_CHECK
void check_GapOption(void)
{
	/* Gap options , page 88 */
	double X1 = 50.0, X2 = 57.0;
	double S = 50.0, T = 0.5, r = 0.09, b = 0.09, v = 0.20;

	double computed = GapOption(1, S, X1, X2, T, r, b, v);
	assert_equal(computed, -0.0053);
}


int main(void)
{
	check_GapOption();
	return 0;
}
#endif

