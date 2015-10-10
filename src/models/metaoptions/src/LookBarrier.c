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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "metaoptions.h"

/* Look-barrier options */
/*
 * Performance notes: We start of slower than most other functions, only 1900 calls/sec...
 * calls/sec	Action
 *    1.900		Adding vst1
 */
/* TODO: 
 *	The variable named trho can easily be replaced with -Rho the 2 places trho is used 
 *	We do "a lot of" 2.0 * b, Maybe we should replace the expression with a variable
 */
double LookBarrier(int type, double S, double X, double H, double t1, double T2, double r, double b, double v)
{
	double vst1, vv, erT2, vsT2, hh, K, mu1, mu2, Rho, eta, m;
	double emu2hv, emu1hv, g1, g2, ta, tb, trho, tp1, tp2, part1, part2, part3, part4; 
	double OutValue, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);
	assert(is_sane(t1));
	assert(is_sane(T2));

	assert(type == SB_CALL_UP_OUT || type == SB_PUT_DOWN_OUT || type == SB_CALL_UP_IN  || type == SB_PUT_DOWN_IN);

	vst1 = v * sqrt(t1);
	assert(is_sane(vst1));

	vv = v*v;
	erT2 = exp(-r * T2);
	vsT2 = v * sqrt(T2);

    hh = log(H / S);
    K = log(X / S);
    mu1 = b - vv / 2.0;
    mu2 = b + vv / 2.0;
	assert(is_sane(mu2));

    Rho = sqrt(t1 / T2);

	if(type == SB_CALL_UP_OUT || type == SB_CALL_UP_IN) {
        eta = 1.0;
        m = fmin(hh,  K);
    }
	else if(type == SB_PUT_DOWN_OUT || type == SB_PUT_DOWN_IN) {
        eta = -1.0;
        m = fmax(hh, K);
    }
	else
		abort();

	/* Some more intermediate values */
	emu2hv = exp(2.0 * mu2 * hh / vv);
	emu1hv = exp(2.0 * mu1 * hh / vv);
    
    g1	= (cnd(eta * (hh - mu2 * t1) / vst1) - emu2hv * cnd(eta * (-hh - mu2 * t1) / vst1)) 
        - (cnd(eta * ( m - mu2 * t1) / vst1) - emu2hv * cnd(eta * (m - 2.0 * hh - mu2 * t1) / vst1));

    g2	= (cnd(eta * (hh - mu1 * t1) / vst1) - emu1hv * cnd(eta * (-hh - mu1 * t1) / vst1)) 
        - (cnd(eta * ( m - mu1 * t1) / vst1) - emu1hv * cnd(eta * (m - 2.0 * hh - mu1 * t1) / vst1));

	ta = eta * (m - mu2 * t1) / vst1;
	assert(is_sane(ta));

	tb = eta * (-K + mu2 * T2) / vsT2;
	assert(is_sane(tb));

	trho = -Rho;
	assert(is_sane(trho));

	tp1 = cbnd(ta, tb, trho);

	ta = eta * (m - 2.0 * hh - mu2 * t1) / vst1;
	assert(is_sane(ta));

	tb = eta * (2.0 * hh - K + mu2 * T2) / vsT2;
	assert(is_sane(tb));

	tp2 = cbnd(ta, tb, trho);
	assert(is_sane(tp2));

    part1 
		= S * exp((b - r) * T2) * (1.0 + vv / (2.0 * b)) 
		* ( tp1 - emu2hv * tp2);

    part2 
		= -erT2 * X 
		* (
			           cbnd(eta * (m - mu1 * t1) / vst1, eta * (-K + mu1 * T2) / vsT2, -Rho) 
			- emu1hv * cbnd(eta * (m - 2.0 * hh - mu1 * t1) / vst1, eta * (2.0 * hh - K + mu1 * T2) / vsT2, -Rho)
		);

    part3 
		= -erT2 * vv / (2.0 * b) 
		* (
			S * pow(S / X, -2.0 * b / vv) * cbnd(eta * (m + mu1 * t1) / vst1, eta * (-K - mu1 * T2) / vsT2, -Rho) 
          - H * pow(H / X, -2.0 * b / vv) * cbnd(eta * (m - 2.0 * hh + mu1 * t1) / vst1, eta * (2.0 * hh - K - mu1 * T2) / vsT2, -Rho)
		);

    part4 
		= S * exp((b - r) * T2) 
		* (
			(1.0 + vv / (2.0 * b)) * cnd(eta * mu2 * (T2 - t1) / (v * sqrt(T2 - t1)))
			+ exp(-b * (T2 - t1)) * (1.0 - vv / (2.0 * b)) * cnd(eta * (-mu1 * (T2 - t1)) / (v * sqrt(T2 - t1)))
		)
		* g1 - erT2 * X * g2;


    OutValue = eta * (part1 + part2 + part3 + part4);
	if(type == SB_CALL_UP_OUT || type == SB_PUT_DOWN_OUT)
        result = OutValue;
	else if(type == SB_CALL_UP_IN)
        result = PartialFixedLB(1, S, X, t1, T2, r, b, v) - OutValue;
	else if(type == SB_PUT_DOWN_IN)
        result = PartialFixedLB(0, S, X, t1, T2, r, b, v) - OutValue;
	else
		abort();

	return result;
}

#ifdef LOOKBARRIER_CHECK

/*
 * NOTE: 
 * Again a formula bombs out because of invalid test data. This time
 * it is LookBarrier() which in the book is "tested" with t1=0.0.
 * There's no way that can work because the formula divides "lots of stuff"
 * with sqrt(t1). When t1 == 0, the division fails.
 * 20070310 boa
 */

void check_LookBarrier(void)
{
	double S = 100.0, X = 100.0, T2 = 1.0, r = 0.10, b = 0.10;
	double result;

	/* Test data for up&out LookBarrier calls 
	 * We combine data for H, t1 and v.
	 */
	struct {
		double v;
		double H;
		double fasit[5];
	} values[6] = {
		{0.15, 110.0, {17.5212,  9.6529,  4.2419,  1.7112, 0.2388}}, 
		{0.15, 120.0, {17.5212, 16.0504, 11.0593,  6.4404, 2.1866}}, 
		{0.15, 130.0, {17.5212, 17.0597, 14.9975, 11.1547, 5.5255}}, 
		{0.30, 110.0, {30.1874,  7.4146,  2.7025,  0.8896, 0.0357}}, 
		{0.30, 120.0, {30.1874, 16.4987,  7.5509,  3.1682, 0.4259}}, 
		{0.30, 130.0, {30.1874, 23.1605, 13.1118,  6.6034, 1.5180}}
	};

	int i, nelem = 6;

	for(i = 0; i < nelem; i++) {
		double t1 = 0.0;
		int j;

		for(t1 = 0.25, j = 1; j < 5; j++, t1 += 0.25) {
			fprintf(stderr, "i/j == %d/%d\n", i, j);
			result = LookBarrier(SB_CALL_UP_OUT, S, X, values[i].H, t1, T2, r, b, values[i].v);
			assert_equal(result, values[i].fasit[j]);
		}
	}
}

int main(void)
{
	check_LookBarrier();
	return 0;
}

#endif

