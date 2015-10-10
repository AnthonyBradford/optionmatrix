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

/*
 * Optimization notes:
 * Calls/sec	Action
 * 110.000		Adding vv variable, which equals v*v
 * 110.000 I assume that we mostly spend time in cbnd(), so there's no point in
 * tuning this function anymore. One could add inline versions, but who cares for
 * such an odd funcion.
 */

/* Writer extendible options */
double ExtendibleWriter(
	int fCall,
	double S,
	double X1,
	double X2,
	double t1,
	double T2,
	double r,
	double b,
	double v) 
{
	const double vv = v * v;

    const double Rho = sqrt(t1 / T2);
    const double z1 = (log(S / X2) + (b + vv / 2.0) * T2) / (v * sqrt(T2));
    const double z2 = (log(S / X1) + (b + vv / 2.0) * t1) / (v * sqrt(t1));

	const double vt1 = sqrt(vv * t1);
	const double vT2 = sqrt(vv * T2);
	const double res1 = gbs(fCall, S, X1, t1, r, b, v);

	double result;
    if (fCall) {
        result = res1
			+ S * exp((b - r) * T2) * cbnd(z1, -z2, -Rho) 
			- X2 * exp(-r * T2) 
			* cbnd(z1 - vT2, -z2 + vt1, -Rho);
    }
	else {
        result 
			= res1
			+ X2 * exp(-r * T2) * cbnd(-z1 + vT2, z2 - vt1, -Rho)
			- S * exp((b - r) * T2) * cbnd(-z1, z2, -Rho);
    }

	return result;
}

#ifdef EXTENDIBLEWRITER_CHECK

/* Page 50-51 */
void check_ExtendibleWriter(void)
{
	double S = 80.0, X1 = 90.0, X2= 82.0, t1 = 0.5, T2 = 0.75, r = 0.10, b = 0.10, v = 0.30;
	double result, fasit = 6.8238;

	result = ExtendibleWriter(1, S, X1, X2, t1, T2, r, b, v);
	assert_equal(result, fasit);
}

int main(void)
{
	check_ExtendibleWriter();
	printf("Mangler data for puts\n");
	return 0;
}
#endif

