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

/* Optimization notes: We start off with 257.000 calls/s, that's the baseline. NOTE that we run
 * a couple of CPU intensive apps at the same time, so the performance varies quite a bit.
 * Calls/s		Change done
 * 257.000		Changing TypeFlag from const char* to integer
 * 252.000		Adding sT variable which replaces all calls to sqrt(T) (11 calls).
 * 252.000		Adding vsT variable which replaces the expression (v * sT) (18 calls)
 * 257.000		Adding the erT variable which replaces exp(-r * T)
 * 259.000		Adding the ebrT variable which replaces exp((b - r) * T). Perf drops, but readability increases...
 * 252.000		Dropping sT variable since it was only used once, when computing vsT.
 * 257.000		Adding the variable pse, which replaces phi * S * ebrT.  This is for readability only!
 * 254.000		Removing ebrT since it was used only once.
 * 252.000		Added the px and pp variables to reduse the # of calls to pow()
 * 257.000		Added HS, which replaces H/S
 * 259.000		Computing f6 on demand only.
 * 297.000		Well, that made a difference! :-) The code is awful, though. Creating a F5 and F6 macro 
 * 309.000		Adding F1-F4 macros as well.
 * 378.000		Added  pp and px macros
 * 411.000		Replaced if/elseif to set eta/phi with a switch() statement.
 * 405.000		Replaced all if/elseif with switch() statements. Added more return points.
 * 417.000		
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "metaoptions.h"


/* Standard barrier options */
double StandardBarrier(
	int typeflag,
	double S,
	double X,
	double H,
	double K,
	double T,
	double r,
	double b,
	double v)
{
	double HS, vsT, erT, mu, lambda, X1, X2, _y1, y2, Z, pse;
    int eta, phi;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	HS = H/S;
	vsT = v * sqrt(T);;
	erT = exp(-r * T) ;
    
    mu = (b - pow2(v) / 2.0) / pow2(v);
    lambda = sqrt(pow2(mu) + 2.0 * r / pow2(v));
    X1 = log(S / X) / vsT + (1.0 + mu) * vsT;
    X2 = log(S / H) / vsT + (1.0 + mu) * vsT;
    _y1 = log(pow2(H) / (S * X)) / vsT + (1.0 + mu) * vsT;
    y2 = log(HS) / vsT + (1.0 + mu) * vsT;
    Z =  log(HS) / vsT + lambda * vsT;
    
	/* Binary variables which is either 1 or -1 */
	switch(typeflag) {
		case SB_CALL_DOWN_IN:
		case SB_CALL_DOWN_OUT:
			eta = 1;
			phi = 1;
			break;
    
		case SB_CALL_UP_IN:
		case SB_CALL_UP_OUT:
			eta = -1;
			phi = 1;
			break;
    
		case SB_PUT_DOWN_IN:
		case SB_PUT_DOWN_OUT:
			eta = 1;
			phi = -1;
			break;

		case SB_PUT_UP_IN:
		case SB_PUT_UP_OUT:
			eta = -1;
			phi = -1;
			break;

		default:
			abort();
	}

	pse = phi * S * exp((b - r) * T);

/* Inline macros to avoid calling cnd() as well as to avoid duplicating formulas. We could of course create
 * inline functions instead, but then we need to pass a lot of params...
 */
#define PX (phi * X * erT * pow(HS, (2.0 * mu)))
#define PP (pse * pow(HS, (2.0 * (mu + 1.0))))

#define F1 (pse * cnd(phi * X1) - phi * X * erT * cnd(phi * X1 - phi * vsT))
#define F2 (pse * cnd(phi * X2) - phi * X * erT * cnd(phi * X2 - phi * vsT))
#define F3 (PP * cnd(eta * _y1) - PX * cnd(eta * _y1 - eta * vsT))
#define F4 (PP * cnd(eta * y2) - PX * cnd(eta * y2 - eta * vsT))
#define F5 (K * erT * (cnd(eta * X2 - eta * vsT) - pow(HS, (2.0 * mu)) * cnd(eta * y2 - eta * vsT)))
#define F6 (K * (pow(HS, (mu + lambda)) * cnd(eta * Z) + pow(HS, (mu - lambda)) * cnd(eta * Z - 2.0 * eta * lambda * vsT)))
    
    if (X > H) {
		switch(typeflag) {
			case SB_CALL_DOWN_IN:	return F3 + F5;
			case SB_CALL_UP_IN:		return F1 + F5;
			case SB_PUT_DOWN_IN:	return F2 - F3 + F4 + F5;
			case SB_PUT_UP_IN:		return F1 - F2 + F4 + F5;
			case SB_CALL_DOWN_OUT:	return F1 - F3 + F6;
			case SB_CALL_UP_OUT:	return F6;
			case SB_PUT_DOWN_OUT:	return F1 - F2 + F3 - F4 + F6;
			case SB_PUT_UP_OUT:		return F2 - F4 + F6;
			default:				abort();
		}
    }
	else if( X < H) {
		switch(typeflag) {
			case SB_CALL_DOWN_IN:	return F1 - F2 + F4 + F5;
			case SB_CALL_UP_IN:		return F2 - F3 + F4 + F5;
			case SB_PUT_DOWN_IN:	return F1 + F5;
			case SB_PUT_UP_IN:		return F3 + F5;
			case SB_CALL_DOWN_OUT:	return F2 + F6 - F4;
			case SB_CALL_UP_OUT:	return F1 - F2 + F3 - F4 + F6;
			case SB_PUT_DOWN_OUT:	return F6;
			case SB_PUT_UP_OUT:		return F1 - F3 + F6;
			default:				abort();
		}
    }
	else {
		switch(typeflag) {
			case SB_CALL_DOWN_IN:	/* fall through */
			case SB_PUT_DOWN_IN:	return F1;
			case SB_CALL_UP_IN:		/* fall through */
			case SB_PUT_UP_IN:		
			case SB_CALL_DOWN_OUT:
			case SB_CALL_UP_OUT:
			case SB_PUT_DOWN_OUT:
			case SB_PUT_UP_OUT:		return F6;
			default:				abort();
		}
	}
}

#ifdef STANDARDBARRIER_CHECK
/*
 * There are many different types of Standard Barrier Options,
 * we compine put|call, down|up and in|out, giving us 8 types.
 * The test data, from table 2-9 on page 72, varies on X, H, v
 * for these option types, giving us a big array of test data.
 */
static void check_StandardBarrier(void)
{
	struct {
		int typeflag;
		double X, H, v025, v030;
	} values[] = {
		{ SB_CALL_DOWN_OUT,  90.0,  95.0,  9.0246,  8.8334 },
		{ SB_CALL_DOWN_OUT, 100.0,  95.0,  6.7924,  7.0285 },
		{ SB_CALL_DOWN_OUT, 110.0,  95.0,  4.8759,  5.4137 },
		{ SB_CALL_DOWN_OUT,  90.0, 100.0,  3.0000,  3.0000 },
		{ SB_CALL_DOWN_OUT, 100.0, 100.0,  3.0000,  3.0000 },
		{ SB_CALL_DOWN_OUT, 110.0, 100.0,  3.0000,  3.0000 },
		{ SB_CALL_UP_OUT,  90.0, 105.0,  2.6789,  2.6341 },
		{ SB_CALL_UP_OUT, 100.0, 105.0,  2.3580,  2.4389 },
		{ SB_CALL_UP_OUT, 110.0, 105.0,  2.3453,  2.4315 },

		{ SB_CALL_DOWN_IN,  90.0,  95.0,  7.7627,  9.0093 },
		{ SB_CALL_DOWN_IN, 100.0,  95.0,  4.0109,  5.1370 },
		{ SB_CALL_DOWN_IN, 110.0,  95.0,  2.0576,  2.8517 },
		{ SB_CALL_DOWN_IN,  90.0, 100.0, 13.8333, 14.8816 },
		{ SB_CALL_DOWN_IN, 100.0, 100.0,  7.8494,  9.2045 },
		{ SB_CALL_DOWN_IN, 110.0, 100.0,  3.9795,  5.3043 },
		{ SB_CALL_UP_IN,  90.0, 105.0, 14.1112, 15.2098 },
		{ SB_CALL_UP_IN, 100.0, 105.0,  8.4482,  9.7278 },
		{ SB_CALL_UP_IN, 110.0, 105.0,  4.5910,  5.8350 },

		{ SB_PUT_DOWN_OUT,  90.0,  95.0,  2.2798,  2.4170 },
		{ SB_PUT_DOWN_OUT, 100.0,  95.0,  2.2947,  2.4258 },
		{ SB_PUT_DOWN_OUT, 110.0,  95.0,  2.6252,  2.6246 },
		{ SB_PUT_DOWN_OUT,  90.0, 100.0,  3.0000,  3.0000 },
		{ SB_PUT_DOWN_OUT, 100.0, 100.0,  3.0000,  3.0000 },
		{ SB_PUT_DOWN_OUT, 110.0, 100.0,  3.0000,  3.0000 },
		{ SB_PUT_UP_OUT,  90.0, 105.0,  3.7760,  4.2293 },
		{ SB_PUT_UP_OUT, 100.0, 105.0,  5.4932,  5.8032 },
		{ SB_PUT_UP_OUT, 110.0, 105.0,  7.5187,  7.5649 },

		{ SB_PUT_DOWN_IN,  90.0,  95.0,  2.9586,  3.8769 },
		{ SB_PUT_DOWN_IN, 100.0,  95.0,  6.5677,  7.7989 },
		{ SB_PUT_DOWN_IN, 110.0,  95.0, 11.9752, 13.3078 },
		{ SB_PUT_DOWN_IN,  90.0, 100.0,  2.2845,  3.3328 },
		{ SB_PUT_DOWN_IN, 100.0, 100.0,  5.9085,  7.2636 },
		{ SB_PUT_DOWN_IN, 110.0, 100.0, 11.6465, 12.9713 },
		{ SB_PUT_UP_IN,  90.0, 105.0,  1.4653,  2.0658 },
		{ SB_PUT_UP_IN, 100.0, 105.0,  3.3721,  4.4226 },
		{ SB_PUT_UP_IN, 110.0, 105.0,  7.0846,  8.3686 }
	};

	double S = 100.0, K = 3.0, T = 0.5, r = 0.08, b = 0.04;
	size_t i, nelem = sizeof(values)/sizeof(values[0]);

	printf("Testing StandardBarrier()...\n");fflush(stdout);
	printf("   NOTE: I had to modify StandardBarrier() to make it work since the\n");
	printf("   original function did not work. Contact Espen Haug for a clarification...");
	for(i = 0; i < nelem; i++) {
		double c025, c030;
		
		c025 = StandardBarrier(values[i].typeflag, S, values[i].X, values[i].H, K, T, r, b, 0.25);
		c030 = StandardBarrier(values[i].typeflag, S, values[i].X, values[i].H, K, T, r, b, 0.30);
		#if 0
		fprintf(stderr, "c025: %f fasit: %f . c030:%f  fasit:%f\n",
			c025, values[i].v025, c030, values[i].v030);
		#endif
		assert_equal(c025, values[i].v025);
		assert_equal(c030, values[i].v030);
	}

	printf("OK\n");
}


int main(void)
{
	check_StandardBarrier();
	return 0;
}
#endif

