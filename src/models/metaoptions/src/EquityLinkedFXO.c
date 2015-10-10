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


/* Equity linked foreign exchange option */
double EquityLinkedFXO(
	int fCall,
	double E,
	double S,
	double X,
	double T,
	double r,
	double rf,
	double q,
	double vS,
	double vE,
	double Rho) 
{
	double d1, d2, XS, ES;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);

    d1 = (log(E / X) + (r - rf + Rho * vS * vE + pow2(vE) / 2.0) * T) / (vE * sqrt(T));
    d2 = d1 - vE * sqrt(T);
	XS = X * S * exp((rf - r - q - Rho * vS * vE) * T);
	ES = E * S * exp(-q * T);

    if(fCall) 
        return ES * cnd(d1)  - XS * cnd(d2);
	else 
        return XS * cnd(-d2) - ES * cnd(-d1);
}

#ifdef EQUITYLINKEDFXO_CHECK

void check_EquityLinkedFXO(void)
{
	double S = 100, E = 1.5, X = 1.52, T = 0.25, r = 0.08, rf = 0.05, q = 0.04, vS = 0.20, vE = 0.12, Rho = -0.40;
	double result, fasit = 4.2089;
	
	result = EquityLinkedFXO(0, E, S, X, T, r, rf, q, vS, vE, Rho);
	assert_equal(result, fasit);
}

int main(void)
{
	check_EquityLinkedFXO();
	printf("Mangler data for calls\n");
	return 0;
}

#endif

