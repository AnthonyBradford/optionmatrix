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


/* Partial-time two asset barrier options */
double PartialTimeTwoAssetBarrier(
	int typeflag,
	double S1,
	double S2,
	double X,
	double H,
	double t1,
	double T2,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho) 
{
    int eta = -1, phi = 1;
	double st1, sT2, logHS2, vv2, st1T2, mu1, mu2, d1, d2, d3, d4, e1, e2, e3, e4, w;

	assert(is_sane(S1) && S1 != 0.0);	/* Cannot be 0 */
	assert(is_sane(S2) && S2 != 0.0);	/* Cannot be 0 */
	assert(is_sane(X) && X != 0.0);	/* Cannot be 0 */
	assert(is_sane(H) && H != 0.0);	/* Cannot be 0 */
	assert(is_sane(t1) && t1 != 0.0);	/* Cannot be 0 */
	assert(is_sane(T2) && T2 != 0.0);	/* Cannot be 0 */
	assert(is_sane(r));
	assert(is_sane(b1));
	assert(is_sane(b2));
	assert(is_sane(v1) && v1 != 0.0);	/* Cannot be 0 */
	assert(is_sane(v2) && v2 != 0.0);	/* Cannot be 0 */
	assert(is_sane(Rho) && Rho != 0.0);

	switch(typeflag) {
		case SB_CALL_DOWN_OUT:
		case SB_PUT_DOWN_OUT:
		case SB_CALL_DOWN_IN:
		case SB_PUT_DOWN_IN:
			phi = -1;
			break;
	}

	switch(typeflag) {
		case SB_CALL_DOWN_OUT:
		case SB_CALL_UP_OUT:
		case SB_CALL_DOWN_IN:
		case SB_CALL_UP_IN:
			eta = 1;
			break;
	}

	st1 = sqrt(t1);
	sT2 = sqrt(T2);
	logHS2 = log(H / S2);
	vv2 = v2 * v2;
	st1T2 = sqrt(t1 / T2);

    mu1 = b1 - pow2(v1) / 2.0;
    mu2 = b2 - vv2 / 2.0;
    d1 = (log(S1 / X) + (mu1 + pow2(v1)) * T2) / (v1 * sT2);
    d2 = d1 - v1 * sT2;
    d3 = d1 + 2.0 * Rho * logHS2 / (v2 * sT2);
    d4 = d2 + 2.0 * Rho * logHS2 / (v2 * sT2);
    e1 = (logHS2 - (mu2 + Rho * v1 * v2) * t1) / (v2 * st1);
    e2 = e1 + Rho * v1 * st1;
    e3 = e1 - 2.0 * logHS2 / (v2 * st1);
    e4 = e2 - 2.0 * logHS2 / (v2 * st1);

    assert(is_sane(mu1));
    assert(is_sane(mu2));
    assert(is_sane(d1));
    assert(is_sane(d2));
    assert(is_sane(d3));
    assert(is_sane(d4));
    assert(is_sane(e1));
    assert(is_sane(e2));
    assert(is_sane(e3));
    assert(is_sane(e4));

    w	= eta * S1 * exp((b1 - r) * T2) * (
			cbnd(eta * d1, phi * e1, -eta * phi * Rho * st1T2) 
			- exp(2.0 * logHS2 * (mu2 + Rho * v1 * v2) / vv2) * cbnd(eta * d3, phi * e3, -eta * phi * Rho * st1T2)
		) 
		- eta * exp(-r * T2) * X 
		* (
			cbnd(eta * d2, phi * e2, -eta * phi * Rho * st1T2) 
			- exp(2.0 * logHS2 * mu2 / vv2) * cbnd(eta * d4, phi * e4, -eta * phi * Rho * st1T2)
		);

	switch(typeflag) {
		case SB_CALL_UP_OUT:
		case SB_CALL_DOWN_OUT:
		case SB_PUT_UP_OUT:
		case SB_PUT_DOWN_OUT: return w;

		case SB_CALL_UP_IN:
		case SB_CALL_DOWN_IN: return gbs_call(S1, X, T2, r, b1, v1) - w;

		case SB_PUT_UP_IN:
		case SB_PUT_DOWN_IN: return gbs_put(S1, X, T2, r, b1, v1) - w;
		default: abort();
	}
}

#ifdef PARTIALTIMETWOASSETBARRIER_CHECK

void check_PartialTimeTwoAssetBarrier(void)
{
	struct {
		int type;
		double Rho;
		double fasit[5];
	} values[6] = {
	{ SB_CALL_DOWN_OUT,  0.5, {14.9758, 12.3793, 10.9409, 10.2337, 9.8185}},
	{ SB_PUT_DOWN_OUT,   0.5, { 5.4595,  3.5109,  2.3609,  1.7502, 1.3607}},
	{ SB_CALL_DOWN_OUT,  0.0, {14.9758, 11.2067,  8.9828,  7.8016, 7.0480}},
	{ SB_PUT_DOWN_OUT,   0.0, { 5.4595,  4.0855,  3.2747,  2.8441, 2.5694}},
	{ SB_CALL_DOWN_OUT, -0.5, {14.9758,  9.8818,  6.8660,  5.2576, 4.2271}},
	{ SB_PUT_DOWN_OUT,  -0.5, { 5.4595,  4.5801,  4.1043,  3.8778, 3.7497}}
	};

	double S1 = 100, S2 = 100, X = 100, H = 85, T2 = 1, r = 0.10, b1 = 0.10, b2 = 0.10, v1 = 0.25, v2 = 0.30;
	size_t i, j;

	for(i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
		int type = values[i].type;
		double Rho = values[i].Rho;
		double t1;

		/* NOTE: If t1 == 0.0, then the function will fail. Why? Because we divide by t1 and division by 0.0
		 * is generally considered to be a bad thing.
		 */
		for(j = 1, t1 = 0.25; j < sizeof(values[0].fasit) / sizeof(values[0].fasit[0]); j++, t1 += 0.25) {
			double fasit = values[i].fasit[j];
			double result = PartialTimeTwoAssetBarrier(type, S1, S2, X, H, t1, T2, r, b1, b2, v1, v2, Rho);
			assert_equal(result, fasit);
		}
	}
}
int main(void)
{
	check_PartialTimeTwoAssetBarrier();
	return 0;
}

#endif

