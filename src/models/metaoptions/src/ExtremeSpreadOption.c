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
#include <stdlib.h>

#include "metaoptions.h"

/* Extreme spread options */
/* TODO: Replace arguments SMin/SMax with Sminmax and leave it to the caller
 * to provice one correct value. We use smax for calls and reverse puts, and
 * smin for reverse calls and puts. 
 *
 * Optimization: We start off with 183.000 calls/sec, which is OK. The function
 * was already optimized a bit, and I won't bother to continue until the 
 * interface is OK.(See above).
 */

/*
 * BIG IMPORTANT NOTE!!!
 * 20070309 boa
 * The function fails if t1 is 0. According to the formula on page 68, the correct expression(see below)
 * is (-m + mu*T2), but for some reason we do (-m + mu*t1). This is obviously an error, but which version
 * is correct? The formula or the Excel implementation we base our code on? 
 * Doesn't matter much because the Excel version fails. We go by the book!
 */
double ExtremeSpreadOption(
	int option_type,
	double S,
	double SMin,
	double SMax,
	double t1,
	double T,
	double r,
	double b,
	double v) 
{
	int eta, kappa;
	double Mo, p2v, mu1, mu, m, e2mu, erT, erTMo, SbrT, x, vsT, result;

	assert_valid_price(S);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);
	assert(T > t1 && "We cannot have negative durations ");
	assert(t1 > 0.0 && "If t1 == 0.0, then v * sqrt(t1) becomes 0.0 and later stuff becomes NaN");

	if (option_type == ESO_CALL || option_type == ESO_REVERSE_CALL) 
		eta = 1;
	else
		eta = -1;
	
	if(option_type == ESO_CALL || option_type == ESO_PUT)
		kappa = 1;
	else
		kappa = -1;
		
	if(kappa * eta == 1)
		Mo = SMax;
	else if(kappa * eta == -1)
		Mo = SMin;
	else
		abort();
	
	p2v = pow2(v);
	mu1 = b - p2v / 2.0;
	mu = mu1 + p2v;
	m = log(Mo / S);
	e2mu = exp(2.0 * mu1 * m / p2v);
	erT = exp(-r * T);
	erTMo = erT * Mo;
	SbrT = S * exp((b - r) * T);
	x = SbrT * (1.0 + p2v / (2.0 * b)) ;
	vsT = v * sqrt(T);

	if (kappa == 1) { /* Extreme Spread Option */
		const double vst1 = v * sqrt(t1);
		result 
			= eta * (
				x * cnd(eta * (-m + mu * T) / vsT)
				- exp(-r * (T - t1)) * SbrT * (1.0 + p2v / (2.0 * b)) * cnd(eta * (-m + mu * t1) / vst1) 
				+ erTMo * cnd(eta * (m - mu1 * T) / vsT)
				- erTMo * p2v / (2.0 * b) * e2mu * cnd(eta * (-m - mu1 * T) / vsT) 
				- erTMo * cnd(eta * (m - mu1 * t1) / vst1)
				+ erTMo * p2v / (2.0 * b) * e2mu * cnd(eta * (-m - mu1 * t1) / vst1)
			);
	}
	else if( kappa == -1) {  /* Reverse Extreme Spread Option */
		double vsTt1 = v * sqrt(T - t1);
		result 
			= -eta * (
				x * cnd(eta * (m - mu * T) / vsT) 
				+ erTMo * cnd(eta * (-m + mu1 * T) / vsT) 
				- erTMo * p2v / (2.0 * b) * e2mu * cnd(eta * (m + mu1 * T) / vsT)
				- SbrT * (1.0 + p2v / (2.0 * b)) * cnd(eta * (-mu * (T - t1)) / vsTt1) 
				- exp(-r * (T - t1)) * SbrT * (1.0 - p2v / (2.0 * b)) * cnd(eta * (mu1 * (T - t1)) / vsTt1)
			);
	}
	else
		abort();

	assert(is_sane(result));
	return result;
}

#ifdef EXTREMESPREADOPTION_CHECK

/* Page 67-69 */
static void check_ExtremeSpreadOption(void)
{
	double S = 100.0, T2 = 1.0, r = 0.10, b = 0.10;
	struct {
		int type;	/* option type */
		double v;	/* Volatility */
		double SM;	/* Smin or Smax depending on type */
		/* We have 4 answers, one for each of 4 time values (t1) */
		double fasit[4];
	} values[12] = {
		/* Extreme spread */
		{ ESO_CALL, 0.15, 100, { 17.5212, 10.6618,  6.7967, 3.3218 } },
		{ ESO_CALL, 0.15, 110, {  9.6924,  8.4878,  5.8519, 2.9676 } },
		{ ESO_CALL, 0.15, 120, {  4.6135,  4.5235,  3.6613, 2.0566 } },
		{ ESO_CALL, 0.30, 100, { 30.1874, 17.4998, 10.9444, 5.2735 } },
		{ ESO_CALL, 0.30, 110, { 22.0828, 16.3674, 10.4668, 5.0942 } },
		{ ESO_CALL, 0.30, 120, { 15.7847, 13.5892,  9.2051, 4.6071 } },

		/* Reverse Extreme spread */
		{ ESO_REVERSE_CALL, 0.15, 100, {  0.0000,  2.7046,  5.7250, 9.3347 } },
		{ ESO_REVERSE_CALL, 0.15,  90, {  3.6267,  6.3314,  9.3517, 12.9615 } },
		{ ESO_REVERSE_CALL, 0.15,  80, { 11.3474, 14.0521, 17.0724, 20.6821 } },
		{ ESO_REVERSE_CALL, 0.30, 100, {  0.0000,  3.6120,  7.8702, 13.3404 } },
		{ ESO_REVERSE_CALL, 0.30,  90, {  1.4769,  5.0890,  9.3471, 14.8173 } },
		{ ESO_REVERSE_CALL, 0.30,  80, {  5.7133,  9.3253, 13.5835, 19.0537 } }
	};

	size_t i, nelem = sizeof(values)/sizeof(values[0]);
	assert(nelem == 12);

	nelem = 1;
	for(i = 0; i < nelem; i++) {
		#if 0
		double c1 = ExtremeSpreadOption(values[i].type, S, values[i].SM, values[i].SM, 0.00, T2, r, b, values[i].v);
		#endif
		double c2 = ExtremeSpreadOption(values[i].type, S, values[i].SM, values[i].SM, 0.25, T2, r, b, values[i].v);
		double c3 = ExtremeSpreadOption(values[i].type, S, values[i].SM, values[i].SM, 0.50, T2, r, b, values[i].v);
		double c4 = ExtremeSpreadOption(values[i].type, S, values[i].SM, values[i].SM, 0.75, T2, r, b, values[i].v);

		#if 0
		assert_equal(c1, values[i].fasit[0]);
		#endif
		assert_equal(c2, values[i].fasit[1]);
		assert_equal(c3, values[i].fasit[2]);
		assert_equal(c4, values[i].fasit[3]);
	}
}

int main(void)
{
	check_ExtremeSpreadOption();
	return 0;
}
#endif

