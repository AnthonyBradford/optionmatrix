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

/* Simple chooser options */
double SimpleChooser(
	double S,
	double X,
	double t1,
	double T2, 
	double r,
	double b,
	double v) 
{
	double d, y, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(t1);
	assert_valid_time(T2);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    d = (log(S / X) + (b + pow2(v) / 2.0) * T2) / (v * sqrt(T2));
    y = (log(S / X) + b * T2 + pow2(v) * t1 / 2.0) / (v * sqrt(t1));
  
    result = S * exp((b - r) * T2)
		* cnd(d) - X * exp(-r * T2) 
		* cnd(d - v * sqrt(T2)) 
		- S * exp((b - r) * T2) * cnd(-y) 
		+ X * exp(-r * T2) * cnd(-y + v * sqrt(t1));

	assert(is_sane(result));
	return result;
}
#ifdef SIMPLECHOOSER_CHECK

void check_SimpleChooser(void)
{
	double S = 50.0, X = 50.0, T2 = 0.5, t1 = 0.25, r = 0.08, b = 0.08, v = 0.25;
	double fasit = 6.1071;

	double result = SimpleChooser(S, X, t1, T2, r, b, v);
	assert_equal(result, fasit);
}


int main(void)
{
	check_SimpleChooser();
	return 0;
}
#endif

