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

#include "metaoptions.h"

/* Trinomial tree */
extern double TrinomialTree(
	int EuropeanOption,
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v,
	double n) /* NOTE: n should probably be made an int . boa 20070316 */
{
	int i, j, z;
	double dt, u, vsdt2, d, pu, pd, pm, Df, result;

	double *pval;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	if( (pval = calloc(2*n + 1, sizeof *pval)) == NULL) {
		abort();
	}

	if(fCall)
		z = 1;
	else
		z = -1;

	dt = T / n;
	u = exp(v * sqrt(2.0 * dt));
	vsdt2 = v * sqrt(dt / 2.0);
	d = exp(-v * sqrt(2.0 * dt));
	pu = pow2((exp(b * dt / 2.0) - exp(-vsdt2)) / (exp(vsdt2) - exp(-vsdt2)));
	pd = pow2((exp(vsdt2) - exp(b * dt / 2.0)) / (exp(vsdt2) - exp(-vsdt2)));
	pm = 1.0 - pu - pd;
	Df = exp(-r * dt);

	for(i = 0; i <= 2 * n; i++) {
		pval[i] = fmax(0.0, z * (S * pow(u, fmax(i - n, 0.0)) * pow(d, fmax(n * 2.0 - n - i, 0.0)) - X));
	}

	for(j = (int)n - 1; j >= 0; j--) {
		for(i = 0; i <= j * 2; i++) {
			if(EuropeanOption) {
				pval[i] = (pu * pval[i + 2] + pm * pval[i + 1] + pd * pval[i]) * Df;
			}
			else {
				pval[i] = fmax(
					(z * (S * pow(u, fmax((double)i - j, 0.0)) * pow(d, fmax((double)j * 2.0 - j - i, 0.0)) - X)),
					(pu * pval[i + 2] + pm * pval[i + 1] + pd * pval [i]) * Df);
			}
		} 
	}

	result = pval[0];
	free(pval);
	assert(is_sane(result));
	return result;
}


