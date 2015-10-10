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


/* Foreign equity option struck in domestic currency */
double ForEquOptInDomCur(
	int fCall,
	double E,
	double S,
	double X,
	double T,
	double r,
	double q,
	double vS,
	double vE,
	double Rho) 
{
	double v, d1, d2;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);

    v = sqrt(pow2(vE) + pow2(vS) + 2.0 * Rho * vE * vS);
    d1 = (log(E * S / X) + (r - q + pow2(v) / 2.0) * T) / (v * sqrt(T));
    d2 = d1 - v * sqrt(T);
   
    if(fCall)
        return E * S * exp(-q * T) * cnd(d1) - X * exp(-r * T) * cnd(d2);
	else 
        return X * exp(-r * T) * cnd(-d2) - E * S * exp(-q * T) * cnd(-d1);
}

#ifdef FOREQUOPTINDOMCUR_CHECK

void check_ForEquOptInDomCur(void)
{
	double S = 100, X = 160, T = 0.5, E = 1.5, r = 0.08, q = 0.05, vs=0.20, ve = 0.12, Rho = 0.45;
	double fasit = 8.3056;

	double result = ForEquOptInDomCur(1, E, S, X, T, r, q, vs, ve, Rho);
	assert_equal(result, fasit);
}

int main(void)
{
	check_ForEquOptInDomCur();
	return 0;
}

#endif



