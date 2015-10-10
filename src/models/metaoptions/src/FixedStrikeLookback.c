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

#include "metaoptions.h"

/* Performance notes(Calls/sec is an average between call&put):
 * Calls/sec	Action
 *  620.000		Added erT and vsT variables to remove redundant calls
 *  647.000		Added ebT, replacing exp(b * T)
 *  663.000		Added vv, replacing pow2(v)
 *  673.000		Misc changes
 *  708.000		Added b2
 *  712.000
 */

/* Fixed strike lookback options */
double FixedStrikeLookback(
	int fCall,
	double S,
	double SMin,
	double SMax,
	double X,
	double T,
	double r,
	double b,
	double v) 
{
	double sT, vsT, vv, erT, ebT, ebrT, m, d1, d2, e1, e2, result;

	/* TODO: Add asserts 20070310 */

	sT = sqrt(T);
	vsT = v * sT;
	vv = v*v;
	erT = exp(-r * T);
	ebT = exp(b * T);
	ebrT = exp((b - r) * T);
    
    if(fCall) 
        m = SMax;
	else 
        m = SMin;
    
    d1 = (log(S / X) + (b + vv / 2.0) * T) / (vsT);
    d2 = d1 - vsT;
    e1 = (log(S / m) + (b + vv / 2.0) * T) / (vsT);
    e2 = e1 -  vsT;

	if(fCall) {
		if (X > m) {
			result 
				= S * ebrT * cnd(d1) 
				- X * erT * cnd(d2) 
				+ S * erT * vv / (2.0 * b) 
				* (-pow((S / X), (-2.0 * b / vv)) * cnd(d1 - 2.0 * b / v * sT) + ebT * cnd(d1));
		}
		else {
			result 
			= erT * (m - X) 
			+ S * ebrT * cnd(e1) 
			- erT * m * cnd(e2) 
			+ S * erT * vv / (2.0 * b) 
			* (-pow((S / m), (-2.0 * b / vv)) * cnd(e1 - 2.0 * b / v * sT) + ebT * cnd(e1));
		}
    }
	else {	/* Put */
		if(X < m) {
			result = -S * ebrT * cnd(-d1) + X * erT * cnd(-d1 + v * sT) 
				+ S * erT * vv / (2.0 * b) 
				* (pow((S / X), (-2.0 * b / vv)) * cnd(-d1 + 2.0 * b / v * sT) - ebT * cnd(-d1));
		}
		else {
			result = erT * (X - m) 
				- S * ebrT 
				* cnd(-e1) + erT * m 
				* cnd(-e1 + vsT) 
				+ erT * vv / (2.0 * b) * S 
				* (pow((S / m), (-2.0 * b / vv)) * cnd(-e1 + 2.0 * b / v * sT) - ebT * cnd(-e1));
		}
	}

	return result;
}

#ifdef FIXEDSTRIKELOOKBACK_CHECK
#include  <stdlib.h>
#include <stdio.h>

/* Page 63-64 */
void check_FixedStrikeLookback(void)
{
	/* We have test data for both puts and calls, with 3 different
	 * volatilities(0.10, 0.20,0.30), as well as 2 time values(0.5 and 1.0)
	 * and 3 strikes. This gives use the following array:
	 */
	const size_t nvol = 3, nelem = 6;
	struct {
		double X, T; 
		double vol[3], calls[3], puts[3];
	} values[6] = {
		{  95.0, 0.5, {0.10, 0.20, 0.30}, { 13.2687, 18.9263, 24.9857}, {0.6899,  4.4448,  8.9213}},
		{ 100.0, 0.5, {0.10, 0.20, 0.30}, {  8.5126, 14.1702, 20.2296}, {3.3917,  8.3177, 13.1579}},
		{ 105.0, 0.5, {0.10, 0.20, 0.30}, {  4.3908,  9.8905, 15.8512}, {8.1478, 13.0739, 17.9140}},
		{  95.0, 1.0, {0.10, 0.20, 0.30}, { 18.3241, 26.0731, 34.7116}, {1.0534,  6.2813, 12.2376}},
		{ 100.0, 1.0, {0.10, 0.20, 0.30}, { 13.8000, 21.5489, 30.1874}, {3.8079, 10.1294, 16.3889}},
		{ 105.0, 1.0, {0.10, 0.20, 0.30}, {  9.5445, 17.2965, 25.9002}, {8.3321, 14.6536, 20.9130}}
	};

	double S = 100.0, Smin = 100.0, Smax = 100.0, r = 0.10, b = 0.10;
	size_t i, v;

	for(i = 0; i < nelem; i++) {
		for(v = 0; v < nvol; v++) {
			double result = FixedStrikeLookback(0, S, Smin, Smax, values[i].X, values[i].T, r, b, values[i].vol[v]);
			assert_equal(result, values[i].puts[v]);
		}
		for(v = 0; v < nvol; v++) {
			double result = FixedStrikeLookback(1, S, Smin, Smax, values[i].X, values[i].T, r, b, values[i].vol[v]);
			assert_equal(result, values[i].calls[v]);
		}
	}
}


int main(void)
{
	check_FixedStrikeLookback();
	return 0;
}
#endif


