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

#include "metaoptions.h"


/* Two asset barrier options */
double TwoAssetBarrier(
	int typeflag,
	double S1,
	double S2,
	double X,
	double H,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho) 
{
	double sT, v2sT, logHS2, mu1, mu2, d1, d2, d3, d4, e1, e2, e3, e4, w;
    double eta;    /* Binary variable: 1 for call options and -1 for put options */
    double phi;	/* Binary variable: 1 for up options and -1 for down options */

	assert_valid_price(S1);
	assert_valid_price(S2);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b1);
	assert_valid_cost_of_carry(b2);
	assert_valid_volatility(v1);
	assert_valid_volatility(v2);
    
    
	sT = sqrt(T);
	v2sT = v2 * sT;
	logHS2 = log(H / S2);
    mu1 = b1 - pow2(v1) / 2.0;
    mu2 = b2 - pow2(v2) / 2.0;
    
/*
 * The book has some errors, including this function. The old, broken version
 * is the original code which matches the testdata in table 2-12. That doesn't
 * help, since the function itself is broken... So we use the new version.
 */
#ifdef USE_OLD_BROKEN_VERSION
    d1 = (log(S1 / X) + (mu1 + pow2(v1) / 2.0) * T) / (v1 * sT);
#else
    d1 = (log(S1 / X) + (mu1 + pow2(v1)) * T) / (v1 * sT);
#endif

    d2 = d1 - v1 * sT;
    d3 = d1 + 2.0 * Rho * logHS2 / v2sT;
    d4 = d2 + 2.0 * Rho * logHS2 / v2sT;
    e1 = (logHS2 - (mu2 + Rho * v1 * v2) * T) / v2sT;
    e2 = e1 + Rho * v1 * sT;
    e3 = e1 - 2.0 * logHS2 / v2sT;
    e4 = e2 - 2.0 * logHS2 / v2sT;
   
	switch(typeflag) {
		case SB_CALL_UP_OUT:
		case SB_CALL_UP_IN:
			eta = phi = 1;
			break;

		case SB_CALL_DOWN_OUT:
		case SB_CALL_DOWN_IN:
			eta = 1;
			phi = -1;
			break;
		case SB_PUT_UP_OUT:
		case SB_PUT_UP_IN:
			eta = -1; 
			phi = 1;
			break;

		case SB_PUT_DOWN_OUT:
		case SB_PUT_DOWN_IN:
			phi = eta = -1;
			break;

		default:
			assert(0);
			abort();
	}

    w	= eta * S1 * exp((b1 - r) * T) * (
			cbnd(eta * d1, phi * e1, -eta * phi * Rho) 
			- exp(2.0 * (mu2 + Rho * v1 * v2) * logHS2 / pow2(v2)) * cbnd(eta * d3, phi * e3, -eta * phi * Rho)
		) 
		- eta * exp(-r * T) * X * (cbnd(eta * d2, phi * e2, -eta * phi * Rho) 
		- exp(2.0 * mu2 * logHS2 / pow2(v2)) * cbnd(eta * d4, phi * e4, -eta * phi * Rho));

	switch(typeflag) {
		case SB_CALL_UP_OUT:
		case SB_CALL_DOWN_OUT:
		case SB_PUT_UP_OUT:
		case SB_PUT_DOWN_OUT:
			return w;

		case SB_CALL_UP_IN:
		case SB_CALL_DOWN_IN:
        return gbs_call(S1, X, T, r, b1, v1) - w;

		case SB_PUT_UP_IN:
		case SB_PUT_DOWN_IN:
			return gbs_put(S1, X, T, r, b1, v1) - w;

		default:
			abort();
	}
}

#ifdef TWOASSETBARRIER_CHECK
void check_TwoAssetBarrier(void)
{
#if 1
	printf("\tCannot test TwoAssetBarrier() since we have no testdata\n");
#else
	/* Test data from table 2-22 on page 81 */
	double S1 = 100.0, S2 = 100.0, T = 0.5, v1 = 0.20, v2 = 0.20, r = 0.08, b1 = 0.08, b2 = 0.08;
	struct {
		int type;
		double X, H, fasit[3];
	} values[12] = {
		{ SB_CALL_DOWN_OUT,  90,  95, {3.2941, 4.9485, 6.6592}},
		{ SB_CALL_DOWN_OUT, 100,  95, {1.4173, 2.6150, 3.8906}},
		{ SB_CALL_DOWN_OUT, 110,  95, {0.4737, 1.1482, 1.8949}},
		{ SB_CALL_UP_OUT,  90, 105, {4.6670, 3.1827, 1.8356}},
		{ SB_CALL_UP_OUT, 100, 105, {2.8198, 1.6819, 0.7367}},
		{ SB_CALL_UP_OUT, 110, 105, {1.4285, 0.7385, 0.2263}},
		{ SB_PUT_DOWN_OUT,  90,  95, {0.6184, 0.3498, 0.1141}},
		{ SB_PUT_DOWN_OUT, 100,  95, {2.0075, 1.2821, 0.6114}},
		{ SB_PUT_DOWN_OUT, 110,  95, {4.3298, 3.0813, 1.8816}},
		{ SB_PUT_UP_OUT,  90, 105, {0.0509, 0.2250, 0.4795}},
		{ SB_PUT_UP_OUT, 100, 105, {0.3042, 0.8246, 1.4811}},
		{ SB_PUT_UP_OUT, 110, 105, {1.0134, 1.9818, 3.0712}}
	};
	size_t i, nelem = sizeof(values) / sizeof(values[0]);
	size_t j;

	for(i = 0; i < nelem; i++) {
		int type = values[i].type;
		double X = values[i].X;
		double H = values[i].H;
		double Rho;

		for(j = 0, Rho = -0.50; j < 3; j++, Rho += 0.50) {
			double result = TwoAssetBarrier(type, S1, S2, X, H, T, r, b1, b2, v1, v2, Rho);
			assert_equal(result, values[i].fasit[j]);
		}
	}

#endif
}



int main(void)
{
	check_TwoAssetBarrier();
	return 77;
}
#endif

