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

/* Executive stock options */
double Executive(int fCall, double S, double X, double T, double r, double b, double v, double lambda) 
{
	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);

    return exp(-lambda * T) * gbs(fCall, S, X, T, r, b, v);
}


extern double Executive_call(double S, double X, double T, double r, double b, double v, double lambda) 
{
	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    return exp(-lambda * T) * gbs_call(S, X, T, r, b, v);
}

extern double Executive_put(double S, double X, double T, double r, double b, double v, double lambda) 
{
	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    return exp(-lambda * T) * gbs_put(S, X, T, r, b, v);
}


#ifdef EXECUTIVE_CHECK
void check_Executive(void)
{
	double S = 60.0, X = 64.0, T = 2, r = 0.07, b = r - 0.03, v = 0.38, lambda = 0.15;
	double result, fasit = 9.1244;

	result = Executive(1, S, X, T, r, b, v, lambda);
	assert_equal(result, fasit);
	assert_equal(result, Executive_call(S, X, T, r, b, v, lambda));
}


int main(void)
{
	check_Executive();
	printf("Mangler data for puts\n");
	return 0;
}
#endif

