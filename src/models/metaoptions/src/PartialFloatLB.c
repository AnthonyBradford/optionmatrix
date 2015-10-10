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
/* Performance notes:
 * 41.000	We start with a general cleanup 
 * 41.000	fn() is hard to improve since most of the time is spent in cbnd().
 */
/* Partial-time floating strike lookback options */
double PartialFloatLB(
	int fCall,
	double S,
	double SMin,
	double SMax,
	double t1,
	double T2,
	double r,
	double b,
	double v,
	double lambda)
{
    double m, part1, part2, part3;
	double vv, st1, sT2, erT2, ebrT2, d1, d2, e1, e2, f1, f2, g1, g2;

	assert_valid_price(S);
	assert_valid_price(SMin);
	assert_valid_price(SMax);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    if(fCall) 
        m = SMin;
	else 
        m = SMax;
    
	vv = v*v;
	st1 = sqrt(t1);
	sT2 = sqrt(T2);
	erT2 = exp(-r * T2);
	ebrT2 = exp((b - r) * T2);

    d1 = (log(S / m) + (b + vv / 2.0) * T2) / (v * sT2);
    d2 = d1 - v * sT2;
    e1 = (b + vv / 2.0) * (T2 - t1) / (v * sqrt(T2 - t1));
    e2 = e1 - v * sqrt(T2 - t1);
    f1 = (log(S / m) + (b + vv / 2.0) * t1) / (v * st1);
    f2 = f1 - v * st1;
    g1 = log(lambda) / (v * sT2);
    g2 = log(lambda) / (v * sqrt(T2 - t1));

    if(fCall) {
        part1 
			= S * ebrT2 * cnd(d1 - g1) 
			- lambda * m * erT2 * cnd(d2 - g1);

        part2 
			= erT2
			* vv / (2.0 * b) 
			* lambda * S 
			* (pow((S / m), (-2.0 * b / vv)) * cbnd(-f1 + 2.0 * b * st1 / v, -d1 + 2.0 * b * sT2 / v - g1, sqrt(t1 / T2)) 
			- exp(b * T2) * pow(lambda, (2.0 * b / vv)) 
			* cbnd(-d1 - g1, e1 + g2, -sqrt(1.0 - t1 / T2))) 
			+ S * ebrT2 * cbnd(-d1 + g1, e1 - g2, -sqrt(1.0 - t1 / T2));

        part3 
			= erT2 * lambda * m * cbnd(-f2, d2 - g1, -sqrt(t1 / T2)) 
			- exp(-b * (T2 - t1)) * ebrT2 * (1.0 + vv / (2.0 * b)) * lambda * S * cnd(e2 - g2) * cnd(-f1);
    
    }
	else {
        part1 
			= lambda * m * erT2 * cnd(-d2 + g1) 
			- S * ebrT2 * cnd(-d1 + g1);

        part2 = -erT2
			* vv / (2.0 * b) * lambda * S 
			* (pow((S / m), (-2.0 * b / vv)) * cbnd(f1 - 2.0 * b * st1 / v, d1 - 2.0 * b * sT2 / v + g1, sqrt(t1 / T2)) 
			- exp(b * T2) * pow(lambda, (2.0 * b / vv)) 
			* cbnd(d1 + g1, -e1 - g2, -sqrt(1.0 - t1 / T2))) 
        - S * ebrT2 * cbnd(d1 - g1, -e1 + g2, -sqrt(1.0 - t1 / T2));

        part3 
			= -erT2 * lambda * m * cbnd(f2, -d2 + g1, -sqrt(t1 / T2)) 
			+ exp(-b * (T2 - t1)) * ebrT2 * (1.0 + vv / (2.0 * b)) * lambda * S * cnd(-e2 + g2) * cnd(f1);
	}
  
	return part1 + part2 + part3;
}

#ifdef PARTIALFLOATLB_CHECK
#include <stdlib.h>
#include <stdio.h>

/* Page 65-66 */
static void check_PartialFloatLB(void)
{
	/* We have test data for puts&calls, both with 3 vol's and three lookback periods. 
	 * We also have 2 values for Smin/max, either 90 or 110.
	 * The array contains S,v,fasit1,fasit2,fasit3, 6 rows.
	 * We check calls first, then puts. 
	 */
	double calls[6][5]  = {
		{  90.0, 0.10,  8.6524,  9.2128,  9.5567 },
		{  90.0, 0.20, 13.3402, 14.5121, 15.3140 },
		{  90.0, 0.30, 17.9831, 19.6618, 20.8493 },
		{ 110.0, 0.10, 10.5751, 11.2601, 11.6804 },
		{ 110.0, 0.20, 16.3047, 17.7370, 18.7171 },
		{ 110.0, 0.30, 21.9793, 24.0311, 25.4825 }
	};

	double put_values[6][5]  = {
		{  90.0, 0.10,  2.7189,  3.4639,  4.1912 },
		{  90.0, 0.20,  7.9153,  9.5825, 11.0362 },
		{  90.0, 0.30, 13.4719, 16.1495, 18.4071 },
		{ 110.0, 0.10,  3.3231,  4.2336,  5.1226 },
		{ 110.0, 0.20,  9.6743, 11.7119, 13.4887 },
		{ 110.0, 0.30, 16.4657, 19.7383, 22.4976 }
	};

	double lambda = 1.0, T2 = 1.0, r = 0.06, b = 0.06;
	size_t i, nelem = 6;

	for(i = 0; i < nelem; i++) {
		double c1, c2, c3;
		c1 = PartialFloatLB(1, calls[i][0], calls[i][0], calls[i][0], 0.25, T2, r, b, calls[i][1], lambda);
		c2 = PartialFloatLB(1, calls[i][0], calls[i][0], calls[i][0], 0.50, T2, r, b, calls[i][1], lambda);
		c3 = PartialFloatLB(1, calls[i][0], calls[i][0], calls[i][0], 0.75, T2, r, b, calls[i][1], lambda);
		assert_equal(c1, calls[i][2]);
		assert_equal(c2, calls[i][3]);
		assert_equal(c3, calls[i][4]);
	}

	for(i = 0; i < nelem; i++) {
		double c1, c2, c3;
		c1 = PartialFloatLB(0, put_values[i][0], put_values[i][0], put_values[i][0], 0.25, T2, r, b, put_values[i][1], lambda);
		c2 = PartialFloatLB(0, put_values[i][0], put_values[i][0], put_values[i][0], 0.50, T2, r, b, put_values[i][1], lambda);
		c3 = PartialFloatLB(0, put_values[i][0], put_values[i][0], put_values[i][0], 0.75, T2, r, b, put_values[i][1], lambda);
		assert_equal(c1, put_values[i][2]);
		assert_equal(c2, put_values[i][3]);
		assert_equal(c3, put_values[i][4]);
	}
}


int main(void)
{
	check_PartialFloatLB();
	return 0;
}
#endif


