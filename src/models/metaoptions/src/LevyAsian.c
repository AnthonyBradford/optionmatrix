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


/* Arithmetic average rate option */
double LevyAsian(
	int fCall,
	double S,
	double SA,
	double X,
	double T,
	double T2,
	double r,
	double b,
	double v) 
{
	double vv, ebrT2, erT2, SE, m, d, ssv, XStar, d1, d2;

	assert_valid_price(S);
	assert_valid_price(SA);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_time(T2);
	assert_valid_interest_rate(r);
	#if 0
		assert_valid_cost_of_carry(b);
	#endif
	assert_valid_volatility(v);

	vv = v*v;
	ebrT2 = exp((b - r) * T2);
	erT2 = exp(-r * T2);

    SE = S / (T * b) * (ebrT2 - erT2);
    m = 2.0 * pow2(S) / (b + vv) * ((exp((2.0 * b + vv) * T2) - 1.0) / (2.0 * b + vv) - (exp(b * T2) - 1.0) / b);
    d = m / (pow2(T));
    ssv = sqrt(log(d) - 2.0 * (r * T2 + log(SE)));
    XStar = X - (T - T2) / T * SA;
    d1 = 1.0 / ssv * (log(d) / 2.0 - log(XStar));
    d2 = d1 - ssv;
    
    if(fCall) 
        return SE * cnd(d1) - XStar * erT2 * cnd(d2);
	else
        return (SE * cnd(d1) - XStar * erT2 * cnd(d2)) - SE + XStar * erT2;
}

#ifdef LEVYASIAN_CHECK

static void check_LevyAsian(void)
{
	double S = 6.80, SA = 6.80, X = 6.90, T = 0.5, T2 = 0.5, r = 0.07, b = -0.02, v = 0.14;

	double result, fasit = 0.2237;

	/* Now for some call options, we have test data in table 2-19, page 100.
	 * We have 3 X, 2 v and 3 T2 and test data for both TurnbullWakeman
	 * as well as Levy's approximation. We only use levy here, but remember
	 * to add testcases in the check_TurnbullWakeman() function as well.
	 */
	double values[3][2][3] = {
		{ {7.0544, 5.6731, 5.0806}, {10.1213, 6.9705, 5.1411}},
		{ {3.7845, 1.9964, 0.6722}, { 7.5038, 4.0687, 1.4222}},
		{ {1.6729, 0.3565, 0.0004}, { 5.4071, 2.1359, 0.1552}}
	};
	size_t iT2, nT2 = 3;
	size_t iv = 0, niv = 2;
	size_t iX = 0, nX = 3;

	/* Test a put */
	result = LevyAsian(0, S, SA, X, T, T2, r, b, v);
	assert_equal(result, fasit);


	S = SA = 100; T = 0.75; r = 0.10; b = 0.05;
	for(iX = 0, X = 95.0; iX < nX; iX++, X += 5.0) {
		for(iv = 0, v = 0.15; iv < niv; iv++, v += 0.20) {
			for(iT2 = 0, T2 = 0.75; iT2 < nT2; iT2++, T2 -= 0.25) {
				fasit = values[iX][iv][iT2];
				result = LevyAsian(1, S, SA, X, T, T2, r, b, v);
				assert_equal(result, fasit);
			}
		}
	}
}

int main(void)
{
	check_LevyAsian();
	return 0;
}
#endif

