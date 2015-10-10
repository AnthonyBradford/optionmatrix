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


/* Geometric average rate option */
double GeometricAverageRateOption(
	int fCall,
	double S,
	double SA,
	double X,
	double T,
	double T2,
	double r,
	double b,
	double v) 
{
	double bA, vA, t1;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);

    bA = 0.5 * (b - pow2(v) / 6.0);
    vA = v / sqrt(3.0);
    t1 = T - T2;
    
    if (t1 > 0.0) {
        X = (t1 + T2) / T2 * X - t1 / T2 * SA;
        return gbs(fCall, S, X, T2, r, bA, vA) * T2 / (t1 + T2);
    }
	else if(t1 == 0.0) 
        return gbs(fCall, S, X, T, r, bA, vA);
	else
		abort();
}

#ifdef GEOMETRICAVERAGERATEOPTION_CHECK

void check_GeometricAverageRateOption(void)
{
	#if 0
	double S = 80.0, X = 85.0, T = 0.25, r = 0.05, b = 0.08, v = 0.20;
	#endif
	printf("	%s(): Not implemented\n", __func__);
}

int main(void)
{
	check_GeometricAverageRateOption();
	return 77;
}

#endif

