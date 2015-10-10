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

#include <stdio.h>
#include <math.h>

#include "metaoptions.h"

extern double BSbisection(int fCall, double S, double X, double T, double r, double b, double price)
{

	double vLow = VOLATILITY_MIN;
	double vHigh = VOLATILITY_MAX, cLow, cHigh;
	double epsilon = 0.000001;

	double val, diff, vi = 0.0;
        int counter = 0;

	for(;;) {

		cLow = BSAmericanApprox(fCall, S, X, T, r, b, vLow);
		cHigh = BSAmericanApprox(fCall, S, X, T, r, b, vHigh);
		if(price < cLow)
			return 0.0; 
		else if(price > cHigh)
			return VOLATILITY_MAX;

		vi = vLow + (price - cLow) * (vHigh - vLow) / (cHigh - cLow);
		if(vi < VOLATILITY_MIN)
			vi = VOLATILITY_MIN;
		else if(vi > VOLATILITY_MAX)	
			vi = VOLATILITY_MAX;

		assert_valid_volatility(vi);
		val = BSAmericanApprox(fCall, S, X, T, r, b, vi);
		diff = price - val;
		if(fabs(diff) <= epsilon)
			break;
		else if(val < price)
			vLow = vi;
		else
			vHigh = vi;

		if( counter++ >= 100 )
		  return 0;

	}

	return vi;
}

#ifdef BSBISECTION_CHECK

void check_bsbisection(void)
{
	double price, computed, facit = 0.35;
	int fCall = 0;

	double S = 75.0, X = 70.0, T = 0.5, r = 0.10, b = 0.05;

	price = gbs(fCall, S, X, T, r, b, facit);
	computed = BSbisection(fCall, S, X, T, r, b, price);
	assert_equal(computed, facit);
}
int main(void)
{
	check_bsbisection();
	return 77;
}

#endif

