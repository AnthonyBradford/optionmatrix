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

double Gamma(double S, double X, double T, double r, double b, double v) 
{
	double vst, d1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
    d1 = (log(S / X) + (b + pow2(v) / 2.0) * T) / vst;

    return exp((b - r) * T) * normdist(d1) / (S * vst);
}

#ifdef GGAMMA_CHECK

void check_gamma(void)
{
	double S = 55.0, X = 60.0, T = 0.75, r = 0.10, b = 0.10, v = 0.30;

	assert_equal(Gamma(S, X, T, r, b, v), 0.0278);
}

int main(void)
{
	check_gamma();
	return 0;
}
#endif


