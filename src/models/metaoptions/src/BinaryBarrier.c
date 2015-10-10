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

/* Binary barrier options */
double BinaryBarrier(
	int typeflag,
	double S,
	double X,
	double H,
	double K,
	double T,
	double r,
	double b,
	double v,
	int eta,
	int phi)
{
	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);

	{ /* Workaround for missing C99 */

	double result = 0.0;
	const double vsT = v * sqrt(T);
	const double ebrT = exp((b - r) * T);
	const double erT = exp(-r * T);
	const double HS = H/S;

    const double mu = (b - pow2(v) / 2.0) / pow2(v);
    const double lambda = sqrt(pow2(mu) + 2.0 * r / pow2(v));
    const double X1 = log(S / X) / vsT + (mu + 1.0) * vsT;
    const double X2 = log(S / H) / vsT + (mu + 1.0) * vsT;
    const double Y1 = log(pow2(H) / (S * X)) / vsT + (mu + 1.0) * vsT;
    const double y2 = log(HS) / vsT + (mu + 1.0) * vsT;
    const double Z  = log(HS) / vsT + lambda * vsT;

	assert(typeflag > 0 && typeflag <= 28);
    
/* Some macros which clarifies the code a bit */
#define a1 (S * ebrT * cnd(phi * X1))
#define b1 (K * erT * cnd(phi * X1 - phi * vsT))
#define a2 (S * ebrT * cnd(phi * X2))
#define b2 (K * erT * cnd(phi * X2 - phi * vsT))
#define a3 (S * ebrT * pow((HS), (2.0 * (mu + 1.0))) * cnd(eta * Y1))
#define b3 (K * erT * pow((HS), (2.0 * mu)) * cnd(eta * Y1 - eta * vsT))
#define a4 (S * ebrT * pow((HS), (2.0 * (mu + 1.0))) * cnd(eta * y2))
#define b4 (K * erT * pow((HS), (2.0 * mu)) * cnd(eta * y2 - eta * vsT))
#define a5 (K * (pow((HS), (mu + lambda)) * cnd(eta * Z) + pow((HS), (mu - lambda)) * cnd(eta * Z - 2.0 * eta * lambda * vsT)))
    
	if(typeflag < 5) {
		return a5;
	}
	else if(typeflag < 7) {
		return b2 + b4;
	}
	else if(typeflag < 9) {
		return a2 + a4;
	}
	else if(typeflag < 11) {
		return b2 - b4;
	}
	else if(typeflag < 13) {
		return a2 - a4;
	}
    else if(X > H) {
		switch(typeflag) {
			case 13: /* fallthrough */
			case 14: return b3;
			case 15: return a3;
			case 16: return a1;
			case 17: return b2 - b3 + b4;
			case 18: return b1 - b2 + b4;
			case 19: return a2 - a3 + a4;
			case 20: return a1 - a2 + a3;
			case 21: return b1 - b3;
			case 22: /* fallthrough */
			case 24: return 0;
			case 23: return a1 - a3;
			case 25: return b1 - b2 + b3 - b4;
			case 26: return b2 - b4;
			case 27: return a1 - a2 + a3 - a4;
			case 28: return a2 - a4;
			default: abort();
		}
    }
	else if(X < H) {
		switch(typeflag) {
			case 13: return b1 - b2 + b4;
			case 14: return b2 - b3 + b4;
			case 15: return a1 - a2 + a4;
			case 16: return a2 - a3 + a4;
			case 17: return b1;
			case 18: return b3;
			case 19: return a1;
			case 20: return a3;
			case 21: return b2 - b4;
			case 22: return b1 - b2 + b3 - b4;
			case 23: return a2 - a4;
			case 24: return a1 - a2 + a3 - a4;
			case 25: /* fallthrough */
			case 27: return 0;

			case 26: return b1 - b3;
			case 28: return a1 - a3;
			default: abort();
		}
    }
	else 
		abort();

	/* We never actually get here */
	return result;
	}
}

#ifdef BINARYBARRIER_CHECK

/* We have lots of testdata for BinaryBarrier Options, there are
 * 28 different types of BB options, see pages 92-95 for more 
 * info on BB options. 
 */
static void check_BinaryBarrier(void)
{
	double H = 100.0, T = 0.5, r = 0.10, b = 0.10, v = 0.20;

	/* Note: K is 15 for all option types(1..28) except for
	 * the types 3 and 4, where K == H. */

	/* We need some distinct values for each type, 
	 * S is either 95 or 105, X is either 102 or 98. 
	 * Simple enough, but we also store K in the array
	 * to be able to loop on a consistent data set.
	 * The option number is arrayindex+1.
	 */
	 struct {
	 	double K, S, X102, X98;
		int eta, phi; /* Values from the list of options, eta==n and phi == Ã¸ */
	} values[28] = {
		{  15.0, 105.0,  9.7264,  9.7264, +1, +1},
		{  15.0,  95.0, 11.6553, 11.6553, -1, +1},

		/* NOTE: According to the text in table 2-18, page 95, 
		 * K should be the same as H for the next two rows. That does not
		 * work, but 15 works fine. We keep 15...
		 * 2005-02-06: Update. The books errata states that the values should be changed for option 3 Ã
		 */
		#ifdef USE_OLD_BROKEN_VERSION
		{ 15.0, 105.0,  9.7264,  9.7264, +1, +1},
		#else
		{ 100.0, 105.0,  68.0848,  68.0848, +1, +1},
		#endif
		{ 15.0,  95.0, 11.6553, 11.6553, -1, +1},
		{  15.0, 105.0,  9.3604,  9.3604, +1, -1},
		{  15.0,  95.0, 11.2223, 11.2223, -1, +1},
		{  15.0, 105.0, 64.8426, 64.8426, +1, -1},
		{  15.0,  95.0, 77.7017, 77.7017, -1, +1},
		{  15.0, 105.0,  4.9081,  4.9081, +1, +1},
		{  15.0,  95.0,  3.0461,  3.0461, -1, -1},
		{  15.0, 105.0, 40.1574, 40.1574, +1, +1},
		{  15.0,  95.0, 17.2983, 17.2983, -1, -1},
		{  15.0, 105.0,  4.9289,  6.2150, +1, +1},
		{  15.0,  95.0,  5.3710,  7.4519, -1, +1},

		{  15.0, 105.0, 37.2782, 45.8530, +1, +1},
		{  15.0,  95.0, 44.5294, 54.9262, -1, +1},
		{  15.0, 105.0,  4.4314,  3.1454, +1, -1},
		{  15.0,  95.0,  5.3297,  3.7704, -1, -1},
		{  15.0, 105.0, 27.5644, 18.9896, +1, -1},
		{  15.0,  95.0, 38.7533, 22.7755, -1, -1},
		{  15.0, 105.0,  4.8758,  4.9081, +1, +1},
		{  15.0,  95.0,  0.0000,  0.0407, -1, +1},
		{  15.0, 105.0, 39.9391, 40.1574, +1, +1},
		{  15.0,  95.0,  0.0000,  0.2676, -1, +1},
		{  15.0, 105.0,  0.0323,  0.0000, +1, -1},
		{  15.0,  95.0,  3.0461,  3.0054, -1, -1},
		{  15.0, 105.0,  0.2183,  0.0000, +1, -1},
		{  15.0,  95.0, 17.2983, 17.0306, -1, -1}
	};

	int i, nelem = sizeof(values) / sizeof(values[0]);
	assert(nelem == 28);

	printf("Testing BinaryBarrier()...");

	for(i = 0; i < nelem; i++) {
		double computed98, computed102;
		double fasit98, fasit102;

		computed98  = BinaryBarrier(i + 1, values[i].S,  98, H, values[i].K, T, r, b, v, values[i].eta, values[i].phi);
		computed102 = BinaryBarrier(i + 1, values[i].S, 102, H, values[i].K, T, r, b, v, values[i].eta, values[i].phi);
		fasit98 = values[i].X98;
		fasit102 = values[i].X102;

		if(fabs(fasit98 - computed98) > 0.001)
			printf("\tindex: %d  c98: %2.5f  f98: %2.5f\n", i, computed98, fasit98);

		if(fabs(fasit102 - computed102) > 0.001)
			printf("\tindex: %d c102: %2.5f f102: %2.5f\n", i, computed102, fasit102);

		#if 0
		printf("\tc98:%f c102:%f\n", computed98, computed102);
		#endif
	}

	printf("Semi OK, see books errata and comments in this source code\n");
}

int main(void)
{
	check_BinaryBarrier();
	return 0;
}
#endif

