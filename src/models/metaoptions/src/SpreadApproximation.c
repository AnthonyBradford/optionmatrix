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

#include "metaoptions.h"

/* Spread option approximation */
double SpreadApproximation(
	int fCall,
	double f1,
	double f2,
	double X,
	double T,
	double r,
	double v1,
	double v2,
	double Rho) 
{
	double f2X, v, F;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v1);
	assert_valid_volatility(v2);

	f2X = f2 + X;
    v = sqrt(pow2(v1) + pow2(v2 * f2 / f2X) - 2.0 * Rho * v1 * v2 * f2 / f2X);
    F = f1 / f2X;
    
    return gbs(fCall, F, 1.0, T, r, 0.0, v) * f2X;
}

#ifdef SPREADAPPROXIMATION_CHECK

void check_SpreadApproximation(void)
{
	double F1 = 28, F2 = 20, X = 7, T = 0.25, r = 0.05, v1 = 0.29, v2 = 0.36, Rho = 0.42;
	double fasit = 2.1670;

	double result = SpreadApproximation(1, F1, F2, X, T, r, v1, v2, Rho);
	assert_equal(result, fasit);
}


int main(void)
{
	check_SpreadApproximation();
	return 0;
}
#endif

