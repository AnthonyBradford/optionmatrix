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

/**
 * NOTE: Til meg selv.
 * Alt denne funksjonen gjør er å tilnærme en volatilitet som
 * passer for å få ut en pris. Epsilon brukes for avrunding/presision.
 *
 * For å få denne til å funke med amerikanske opsjoner er det
 * bare å bytte ut kallet til gbs() med en funksjon som beregner
 * pris på amerikanske opsjoner. Det er det hele, intet magisk.
 * 2003-08-25
 */
extern int bisection(
	int fCall, 
	double S,
	double X,
	double T,
	double r,
	double b,
	double price,
	double *piv)
{
	double vLow = VOLATILITY_MIN;
	double vHigh = VOLATILITY_MAX;
	const double epsilon = 0.00000001;
	double vi, val, cLow, cHigh;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);

	for(;;) {
		cLow = gbs(fCall, S, X, T, r, b, vLow);
		cHigh = gbs(fCall, S, X, T, r, b, vHigh);

		/* 
		 * If price < cLow, then it is impossible to compute a proper
		 * implied volatility. This because that volatility would be
		 * greater than VOLATILITY_MIN. Now what?
		 * Another condition is when price > cHigh. When that happens,
		 * IV is way above VOLATILITY_MAX. 
		 */
		if(price < cLow || price > cHigh)
			return 0; 

		vi = vLow + (price - cLow) * (vHigh - vLow) / (cHigh - cLow);
#if 0
		if(vi < VOLATILITY_MIN)
			vi = VOLATILITY_MIN;
		else if(vi > VOLATILITY_MAX)	
			vi = VOLATILITY_MAX;

		assert_valid_volatility(vi);
#endif
		val = gbs(fCall, S, X, T, r, b, vi);
		if(fabs(price - val) <= epsilon)
			break;
		else if(val < price)
			vLow = vi;
		else
			vHigh = vi;
	}

	*piv = vi;
	return 1;
}

#ifdef BISECTION_CHECK
/* bisection for imp. vol of european options */
void check_bisection(void)
{
	double price, computed, facit = 0.35;
	int ok, fCall = 0;

	double S = 75.0, X = 70.0, T = 0.5, r = 0.10, b = 0.05;

	price = gbs(fCall, S, X, T, r, b, facit);
	ok = bisection(fCall, S, X, T, r, b, price, &computed);
	assert(ok);
	assert_equal(computed, facit);
}

int main(void)
{
	check_bisection();
	return 0;
}

#endif


