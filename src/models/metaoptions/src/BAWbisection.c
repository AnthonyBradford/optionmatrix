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

#include <stdio.h>
#include <math.h>

#include "metaoptions.h"

extern double BAWbisection(
	int fCall, 
	double S,
	double X,
	double T,
	double r,
	double b,
	double price)
{
	double vLow = 0.1;
	double vHigh = 1.0;
	const double epsilon = 0.000001;
	double vi;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);

	for(;;) {
		double val;
		const double cLow = BAWAmericanApprox(fCall, S, X, T, r, b, vLow);
		const double cHigh = BAWAmericanApprox(fCall, S, X, T, r, b, vHigh);
		if(cLow == cHigh) {
			/* Happens for deep ITM options. No volatility present */
			return 0.0;
		}
		else if((cHigh - cLow) < 0.001) {
			/* Happens for deep ITM options. No volatility present */
			return 0.0;
		}

		vi = vLow + (price - cLow) * (vHigh - vLow) / (cHigh - cLow);
		if(vi < 0.0 || vi > 1.0) {
			/* Probably a very deep ITM/OTM option causing (cHigh - cLow)
			 * to become extremely low. */

			#if 0
			fprintf(stderr, "price:%f\n", price);
			fprintf(stderr, "vLow :%f\n", vLow);
			fprintf(stderr, "vHigh:%f\n", vHigh);
			fprintf(stderr, "cLow :%f\n", cLow);
			fprintf(stderr, "cHigh:%f\n", cHigh);
			fprintf(stderr, "vi:%f\n", vi);
			#endif
			return 0.0;
		}

		assert(is_sane(vi));
		val = BAWAmericanApprox(fCall, S, X, T, r, b, vi);

		#if 0
		fprintf(stderr,"X %f price %f cl %f ch %f vl %f vh %f vi %f (val):%f\n",
			X, price, cLow, cHigh, vLow, vHigh, vi, val);
		#endif

		if(fabs(price - val) <= epsilon)
			break;
		else if(val < price)
			vLow = vi;
		else
			vHigh = vi;
	}

	return vi;
}

#ifdef BAWBISECTION_CHECK

static void check_BAWbisection(void)
{
	double S=32.420000000000002; 
	double X=10.0;
	double T=0.06575342465753424;
	double r=0.375;
	double b=0.0;
	double price = 5.2704;

	printf("\tiv returned: %f\n", BAWbisection(0, S, X, T, r, b, price));
	printf("\tOK(as in \"not working...\")\n");
}


int main(void)
{
	check_BAWbisection();
	return 0;
}
#endif

