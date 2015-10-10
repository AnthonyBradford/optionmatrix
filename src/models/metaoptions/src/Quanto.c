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


/* Fixed exchange rate foreign equity options-- Quantos */
double Quanto(
	int fCall,
	double Ep,
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
	double d1, d2, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);


    d1 = (log(S / X) + (rf - q - Rho * vS * vE + pow2(vS) / 2.0) * T) / (vS * sqrt(T));
    d2 = d1 - vS * sqrt(T);
   
    if(fCall)
        result = Ep * (S * exp((rf - r - q - Rho * vS * vE) * T) * cnd(d1) - X * exp(-r * T) * cnd(d2));
	else 
        result = Ep * (X * exp(-r * T) * cnd(-d2) - S * exp((rf - r - q - Rho * vS * vE) * T) * cnd(-d1));
    
	assert(is_sane(result));
	return result;
}

#ifdef QUANTO_CHECK

void check_Quanto(void)
{
	double S = 100.0, X = 105.0, T = 0.5, Ep = 1.5, r = 0.08, rf = 0.05, 
		q = 0.04, vS = 0.20, vE = 0.10, Rho = 0.30;
	double fasit = 5.3280;

	double result = Quanto(1, Ep, S, X, T, r, rf, q, vS, vE, Rho);
	assert_equal(result, fasit);
}

int main(void)
{
	check_Quanto();
	return 0;
}

#endif

