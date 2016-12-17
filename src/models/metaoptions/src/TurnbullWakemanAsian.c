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


/* Arithmetic average rate option */
double TurnbullWakemanAsian(
	int fCall,
	double S,
	double SA,
	double X,
	double T,
	double T2,
	double tau,
	double r,
	double b,
	double v) 
{
	double m1, m2, bA, vA, t1, result;
	double b2, vv, bvv, b2vv, t22;

	assert_valid_price(S);
	assert_valid_price(SA);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_time(T2);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	b2 = b * 2.0;
	vv= v * v;
	bvv = b+vv;
	b2vv = b2 + vv;
	t22 = pow(T2-tau, 2.0);

    m1 = b ? (exp(b * T2) - exp(b * tau)) / (b * (T2 - tau)) : 1.0;
    m2 	= 2.0 * exp(b2vv * T2)  / (bvv * b2vv * t22) 
		+ 2.0 * exp(b2vv * tau) / (b * t22) 
		* (1.0 / b2vv - exp(b * (T2 - tau)) / bvv);
    
    bA = log(m1) / T2;
    vA = sqrt(log(m2) / T2 - 2.0 * bA);
    t1 = T - T2;
    
    if (t1 > 0) {
        X = T / T2 * X - t1 / T2 * SA;
        result = gbs(fCall, S, X, T2, r, bA, vA) * T2 / T;
	}
    else
        result = gbs(fCall, S, X, T2, r, bA, vA);

    return result;
}

#ifdef TURNBULLWAKEMANASIAN_CHECK
void check_TurnbullWakemanAsian(void)
{
	double S = 90.0, SA = 88, X = 95.0, T = 0.5, T2 = 0.25, tau = 0.0, r = 0.07, b = 0.02, v = 0.25;
	double result, fasit = 5.8482;

	result = TurnbullWakemanAsian(0, S, SA, X, T, T2, tau, r, b, v);
	assert_equal(result, fasit);

	#if 0
	/*NOTE(20050210): The testdata are incorrect and the function has
	 * errata on www.espenhaug.com. It works for puts, but not for calls.)
	 * It seems to compute the same results as LevyAsian() when there is
	 * an error in the test data.
	 * The test data is OK when T2 == 0.75, but not when T2 == 0.5|0.25. 
	 * If I reintroduce the bug described in the errata, then the test data
	 * is OK. Odd...
	 */
	/* Now for some call options, we have test data in table 2-19, page 100. */
	double values[3][2][3] = {
		{ {7.0544, 5.6748, 5.0810}, {10.1213, 6.9793, 5.1432}},
		{ {3.7845, 1.9996, 0.6745}, { 7.5038, 4.0795, 1.4299}},
		{ {1.6729, 0.3584, 0.0005}, { 5.4071, 2.1461, 0.1587}}
	};

	size_t iT2, nT2 = 3;
	size_t iv = 0, niv = 2;
	size_t iX = 0, nX = 3;

	S = SA = 100; T = 0.75; r = 0.10; b = 0.05;
	for(iX = 0, X = 95.0; iX < nX; iX++, X += 5.0) {
		for(iv = 0, v = 0.15; iv < niv; iv++, v += 0.20) {
			for(iT2 = 0, T2 = 0.75; iT2 < nT2; iT2++, T2 -= 0.25) {
				double c, fasit = values[iX][iv][iT2];
				c = TurnbullWakemanAsian(1, S, SA, X, T, T2, tau, r, b, v);
				//assert_equal(c, fasit);
				fprintf(stderr, "foo: c(%.4f) fasit(%.4f)", c, fasit);
				if(fabs(c - fasit) < 0.0001)
					fprintf(stderr, " Match!");
				fprintf(stderr, "\n");
			}
		}
	}
	#endif
}


int main(void)
{
	check_TurnbullWakemanAsian();
	return 0;
}
#endif

