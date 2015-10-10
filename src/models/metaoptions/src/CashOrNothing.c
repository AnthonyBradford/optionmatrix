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

/* Cash-or-nothing options */
double CashOrNothing(int fCall, double S, double X, double K, double T, double r, double b, double v) 
{
	double d;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    d = (log(S / X) + (b - pow2(v) / 2.0) * T) / (v * sqrt(T));

    if(fCall)
		return K * exp(-r * T) * cnd(d);
	else 
        return K * exp(-r * T) * cnd(-d);
}

#ifdef CASHORNOTHING_CHECK

void check_CashOrNothing(void)
{
	double S = 100.0, X = 80.0, K = 10.0, T = 0.75, r = 0.06, b = 0.0, v = 0.35;
	double computed, fasit = 2.6710;

	computed = CashOrNothing(0, S, X, K, T, r, b, v);
	assert_equal(computed, fasit);
}

int main(void)
{
	check_CashOrNothing();
	printf("Mangler data for calls\n");
	return 0;
}

#endif

