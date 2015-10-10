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

/*
 * Performance notes:
 * Calls/sec	Action
 * 48.000		General cleanup. Not much to do, this function calls cbnd() a lot...
 */

/* Partial-time fixed strike lookback options */
double  PartialFixedLB(
	int fCall,
	double S,
	double X,
	double t1,
	double T2,
	double r,
	double b,
	double v) 
{
	double vv, erT2, b2, vst1, sT2, s1, ebrT2, d1, d2, e1, e2, f1, f2, x, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(t1);
	assert_valid_time(T2);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	vv = v*v;
	erT2 = exp(-r * T2);
	b2 = b*2.0;
	vst1 = v * sqrt(t1);
	sT2 = sqrt(T2);
	s1 = sqrt(1.0 - t1/T2);
	ebrT2 = exp((b - r) * T2);

    d1 = (log(S / X) + (b + vv / 2.0) * T2) / (v * sT2);
    d2 = d1 - v * sT2;
    e1 = ((b + vv / 2.0) * (T2 - t1)) / (v * sqrt(T2 - t1));
    e2 = e1 - v * sqrt(T2 - t1);
    f1 = (log(S / X) + (b + vv / 2.0) * t1) / (vst1);
    f2 = f1 - vst1;

	x = S * erT2 * vv / b2;

    if(fCall) {
        result 
			= S * ebrT2 * cnd(d1) 
			- X * erT2 * cnd(d2) 
			+ x * (-pow((S / X), (-b2 / vv)) * cbnd(d1 - b2 * sT2 / v, -f1 + b2 * sqrt(t1) / v, -sqrt(t1 / T2)) + exp(b * T2) * cbnd(e1, d1, s1)) 
			- S * ebrT2 * cbnd(-e1, d1, -s1) 
			- X * erT2 * cbnd(f2, -d2, -sqrt(t1 / T2)) 
			+ exp(-b * (T2 - t1)) * (1.0 - vv / b2) * S * ebrT2 * cnd(f1) * cnd(-e2);
    }
	else {
        result 
			= X * erT2 * cnd(-d2) 
			- S * ebrT2 * cnd(-d1) 
			+ x * (pow((S / X), (-b2 / vv)) * cbnd(-d1 + b2 * sT2 / v, f1 - b2 * sqrt(t1) / v, -sqrt(t1 / T2)) - exp(b * T2) * cbnd(-e1, -d1, s1))
			+ S * ebrT2 * cbnd(e1, -d1, -s1)
			+ X * erT2 * cbnd(-f2, d2, -sqrt(t1 / T2)) 
			- exp(-b * (T2 - t1)) * (1.0 - vv / b2) * S * ebrT2 * cnd(-f1) * cnd(e2);
    }

	return result;
}

#ifdef PARTIALFIXEDLB_CHECK

#include <stdlib.h>
#include <stdio.h>

/* Page 66-67 */
void check_PartialFixedLB(void)
{
	/* We have test data for puts&calls, both with 3 vol's and three lookback periods. 
	 * We also have 2 values for X, either 90 or 110.
	 * The array contains X,v,fasit1,fasit2,fasit3, 6 rows.
	 * We check calls first, then puts. 
	 */
	double calls[6][5]  = {
		{  90.0, 0.10, 20.2845, 19.6239, 18.6244 },
		{  90.0, 0.20, 27.5385, 25.8126, 23.4957 },
		{  90.0, 0.30, 35.4578, 32.7172, 29.1473 },
		{ 110.0, 0.10,  4.0432,  3.9580,  3.7015 },
		{ 110.0, 0.20, 11.4895, 10.8995,  9.8244 },
		{ 110.0, 0.30, 19.7250, 18.4025, 16.2976 },
	};

	double put_values[6][5]  = {
		{  90.0, 0.10,  0.4973,  0.4632,  0.3863 },
		{  90.0, 0.20,  4.5863,  4.1925,  3.5831 },
		{  90.0, 0.30,  9.9348,  9.1111,  7.9267 },
		{ 110.0, 0.10, 12.6978, 10.9492,  9.1555 },
		{ 110.0, 0.20, 19.0255, 16.9433, 14.6505 },
		{ 110.0, 0.30, 25.2112, 22.8217, 20.0566 },
	};

	double S = 100.0, T2 = 1.0, r = 0.06, b = 0.06;
	size_t i, nelem = 6;

	for(i = 0; i < nelem; i++) {
		double c1, c2, c3;
		c1 = PartialFixedLB(1, S, calls[i][0], 0.25, T2, r, b, calls[i][1]);
		c2 = PartialFixedLB(1, S, calls[i][0], 0.50, T2, r, b, calls[i][1]);
		c3 = PartialFixedLB(1, S, calls[i][0], 0.75, T2, r, b, calls[i][1]);
		assert_equal(c1, calls[i][2]);
		assert_equal(c2, calls[i][3]);
		assert_equal(c3, calls[i][4]);
	}

	for(i = 0; i < nelem; i++) {
		double c1, c2, c3;
		c1 = PartialFixedLB(0, S, put_values[i][0], 0.25, T2, r, b, put_values[i][1]);
		c2 = PartialFixedLB(0, S, put_values[i][0], 0.50, T2, r, b, put_values[i][1]);
		c3 = PartialFixedLB(0, S, put_values[i][0], 0.75, T2, r, b, put_values[i][1]);
		assert_equal(c1, put_values[i][2]);
		assert_equal(c2, put_values[i][3]);
		assert_equal(c3, put_values[i][4]);
	}
}



int main(void)
{
	check_PartialFixedLB();
	return 0;
}

#endif

