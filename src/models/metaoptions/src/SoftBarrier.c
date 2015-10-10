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
#include <assert.h>
#include <stdio.h>

#include "metaoptions.h"

/* Debugging Notes:
 * - The original code had the expression 1 / 2 * ..., which obviously was broken. I changed
 *   it to 0.5 and then everything worked.
 * - I have carefully cleaned up the code a little, to make it look more like the formula
 *   in the book(page 86)
 * - Current error is that Value becomes inf. That is/was because we divide a number by (U - L).
 *   when U == L, we divide by zero, not a good thing.
 *
 * Performance notes:
 */
/* Soft barrier options */
double SoftBarrier(
	int typeflag,
	double S,
	double X,
	double L,
	double U,
	double T,
	double r,
	double b,
	double v) 
{
	double eta, SX, sT, vsT, vv, UU, LL, mu, lambda1, lambda2, d1, d2, d3, d4, e1, e2, e3, e4, w;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	assert(U != L); /* Will cause a divide by zero */

	SX = S * X;
	sT = sqrt(T);
	vsT = v * sT;
	vv = v*v;
	UU = U*U;
	LL = L*L;

    
	if(typeflag == SB_CALL_DOWN_IN || typeflag == SB_CALL_DOWN_OUT)
        eta = 1.0;
    else
        eta = -1.0;
    
    mu = (b + vv / 2.0) / vv;
    lambda1 = exp(-0.5 * vv * T * (mu + 0.5) * (mu - 0.5));
    lambda2 = exp(-0.5 * vv * T * (mu - 0.5) * (mu - 1.5));
    d1 = log(UU / SX) / vsT + mu * vsT;
    d2 = d1 - (mu + 0.5) * vsT;
    d3 = log(UU / SX) / vsT + (mu - 1.0) * vsT;
    d4 = d3 - (mu - 0.5) * vsT;
    e1 = log(LL / SX) / vsT + mu * vsT;
    e2 = e1 - (mu + 0.5) * vsT;
    e3 = log(LL / SX) / vsT + (mu - 1.0) * vsT;
    e4 = e3 - (mu - 0.5) * vsT;
    
    w	= eta * 1.0 / (U - L) 
		* (
			S * exp((b - r) * T) * pow(S, (-2.0 * mu))
			* pow(SX, (mu + 0.5)) / (2.0 * (mu + 0.5)) 
			* (
				pow(UU / SX, mu + 0.5) * cnd(eta * d1) 
				- lambda1 * cnd(eta * d2) 
				- pow(LL / SX, mu + 0.5) * cnd(eta * e1) + lambda1 * cnd(eta * e2)
			) 
			- X * exp(-r * T) * pow(S, (-2.0 * (mu - 1.0)))
			* pow(SX, mu - 0.5) / (2.0 * (mu - 0.5)) 
			* (
				pow(UU / SX, mu - 0.5) * cnd(eta * d3) 
				- lambda2 * cnd(eta * d4) 
				- pow(LL / SX, mu - 0.5) * cnd(eta * e3) + lambda2 * cnd(eta * e4)
			)
		);

   assert(is_sane(w));
   if(typeflag == SB_CALL_DOWN_IN || typeflag == SB_PUT_UP_IN) 
        return w;
	else if(typeflag == SB_CALL_DOWN_OUT) 
        return gbs_call(S, X, T, r, b, v) - w;
	else if(typeflag == SB_PUT_UP_OUT)
        return gbs_put(S, X, T, r, b, v) - w;
	else
		abort();
}

#ifdef SOFTBARRIER_CHECK

/* Page 87, data from table 2-15 */
void check_SoftBarrier(void)
{
	double S = 100.0, X = 100.0, U = 95.0, r = 0.10, b = 0.05;

	/* We have data for a variation of 2 T times 3 v times 10 L */
	double values[10][2][3] = {
		{{3.8075, 4.5263, 4.7297}, {5.4187, 5.3614, 5.2300}},
		{{4.0175, 5.5615, 6.2595}, {6.0758, 6.9776, 7.2046}},
		{{4.0529, 6.0394, 7.2496}, {6.2641, 7.9662, 8.7092}},
		{{4.0648, 6.2594, 7.8567}, {6.3336, 8.5432, 9.8118}},
		{{4.0708, 6.3740, 8.2253}, {6.3685, 8.8822, 10.5964}},
		{{4.0744, 6.4429, 8.4578}, {6.3894, 9.0931, 11.1476}},
		{{4.0768, 6.4889, 8.6142}, {6.4034, 9.2343, 11.5384}},
		{{4.0785, 6.5217, 8.7260}, {6.4133, 9.3353, 11.8228}},
		{{4.0798, 6.5463, 8.8099}, {6.4208, 9.4110, 12.0369}},
		{{4.0808, 6.5654, 8.8751}, {6.4266, 9.4698, 12.2036}}
	};

	/* Now we loop on L, T and v */
	size_t i, j, k;
	double L, T, v;

	/* Note that we start off from row ONE, not zero. That's because the test data contains
	 * a case where Upper == Lower, causing the function to return -inf.
	 */
	for(i = 1, L = 90.0; i < 10; i++, L -= 5.0) {
		for(j = 0, T = 0.5; j < 2; j++, T += 0.5) {
			for(k = 0, v = 0.10; k < 3; k++, v += 0.10) {
				double computed = SoftBarrier(SB_CALL_DOWN_OUT, S, X, L, U, T, r, b, v);
				assert_equal(computed, values[i][j][k]);
			}
		}
	}
}

int main(void)
{
	check_SoftBarrier();
	return 0;
}
#endif

