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
#include <math.h>

#include "metaoptions.h"

/* Cox-Ross-Rubinstein binomial tree */
extern double CRRBinomial(
	int EuropeanOption,
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v,
	int n)
{
	double z, dt, u, d, p, Df, result;
	int i, j;
	double *OptionValue;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);
	assert(n > 0);

	if( (OptionValue = calloc(n + 1, sizeof *OptionValue)) == NULL)
		abort();

	if(fCall)
		z = 1.0;
	else 
		z = -1.0;
		
	dt = T / n;
	u = exp(v * sqrt(dt));
	d = 1.0 / u;
	p = (exp(b * dt) - d) / (u - d);
	Df = exp(-r * dt);
		
	for(i = 0; i <= n; i++)
		OptionValue[i] = fmax(0.0, z * (S * pow(u, (double)i) * pow(d, (double)(n - i)) - X));
	
	for(j = n - 1; j >= 0; j--) {
		for(i = 0; i <= j; i++) {
			if(EuropeanOption)
				OptionValue[i] = (p * OptionValue[i + 1] + (1 - p) * OptionValue[i]) * Df;
			else
				OptionValue[i] = fmax(
					(z * (S * pow(u, (double)i) * pow(d, (double)abs(i - j)) - X)),
					(p * OptionValue[i + 1] + (1 - p) * OptionValue[i]) * Df);
		}
	}

	result = OptionValue[0];
	assert(is_sane(result));
	free(OptionValue);
	return result;
}

