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

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "metaoptions.h"

/* European and American barrier options in binomial trees */
extern double BarrierBinomial(
	int EuropeanOption,
	int type,
	double S,
	double X,
	double H,
	double T,
	double r,
	double b,
	double v,
	int n)
{
	double result, AssetPrice;
	int i, j, phi, z;
	double dt, u, d, p, Df;
	double *pval;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	if( (pval = calloc(n + 10240, sizeof *pval)) == NULL) {
		abort();
	}

	for(i = 1; i <= 100; i++) {
		int x = (int)(pow2(i) * pow2(v) * T / pow2(log(S / H)));
		if(n < x) {
			n = x;
			break;
		}
	}

	if(type == SB_CALL_UP_OUT || type == SB_CALL_DOWN_OUT)
		z = 1;
	else if(type == SB_PUT_UP_OUT || type == SB_PUT_DOWN_OUT)
		z = -1;
	else 
		abort();

	if(type == SB_CALL_UP_OUT || type == SB_PUT_UP_OUT)
		phi = 1;
	else if(type == SB_CALL_DOWN_OUT || type == SB_PUT_DOWN_OUT)
		phi = -1;
	else
		abort();

	dt = T / n;
	u = exp(v * sqrt(dt));
	d = 1.0 / u;
	p = (exp(b * dt) - d) / (u - d);
	Df = exp(-r * dt);

	for(i = 0; i <= n; i++) 
		pval[i] = fmax(0.0, z * (S * pow(u, (double)i) * pow(d, (double)(n - i)) - X));

	for(j = n - 1; j >= 0; j--) {
		for(i = 0; i <= j; i++) {
			AssetPrice = S * pow(u, (double)i) * pow(d, (double)abs(i - j));

			if(phi == 1) {
				if(EuropeanOption && AssetPrice < H) {
					pval[i] = (p * pval[i + 1] + (1.0 - p) * pval[i]) * Df;
				}
				else if(!EuropeanOption && AssetPrice < H) {
					pval[i] = fmax((z * (AssetPrice - X)), (p * pval[i + 1] + (1 - p) * pval[i]) * Df);
				}
				else if(AssetPrice >= H) {
					pval[i] = 0.0;
				}
				else if(EuropeanOption && AssetPrice > H) {
					pval[i] = (p * pval[i + 1] + (1.0 - p) * pval[i]) * Df;
				}
				else if(!EuropeanOption && AssetPrice > H) {
					pval[i] = fmax((z * (AssetPrice - X)), (p * pval[i + 1] + (1.0 - p) * pval [i]) * Df);
				}
				else if(AssetPrice <= H) {
					pval[i] = 0.0;
				}
			} 
		}
	}

	result = pval[0];
	free(pval);
	return result;
}

