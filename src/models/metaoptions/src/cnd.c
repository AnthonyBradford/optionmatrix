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

#include "metaoptions.h"

#include <math.h>

double cnd(double x)
{
	static const double 
		a1 = +0.31938153,
		a2 = -0.356563782,
		a3 = +1.781477937,
		a4 = -1.821255978,
		a5 = +1.330274429;

	const double L = fabs(x);
	const double K = 1.0 / (1.0 + (0.2316419 * L));
	const double a12345k 
		= (a1 * K)
		+ (a2 * K * K) 
		+ (a3 * K * K * K) 
		+ (a4 * K * K * K * K) 
		+ (a5 * K * K * K * K * K); 

	double result = 1.0 - one_div_sqrt2pi * exp(-pow2(L) / 2.0) * a12345k;
		
	assert(is_sane(x));
	if(x < 0.0) 
		result = 1.0 - result;

	assert(is_sane(x));
	return result;
}

#ifdef CND_CHECK
#include <stdio.h>

int main(void)
{
	int i;

	for(i = 0; i < 10; i++) 
		printf("cnd(%i) == %g\n", i, cnd(i));

	return 77;
}

#endif

