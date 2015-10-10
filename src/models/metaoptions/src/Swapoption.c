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

/*  Black-76 European swap option */
extern double Swapoption(int fCall, double t1, double m, double F, double X, double T, double r, double v)
{
	double d1, d2, result;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

 
    d1 = (log(F / X) + pow2(v) / 2.0 * T) / (v * sqrt(T));
    d2 = d1 - v * sqrt(T);

    if(fCall) {  /* Payer swaption */
        result 
			= ((1.0 - 1.0 / pow((1 + F / m), (t1 * m))) / F) 
			* exp(-r * T) * (F * cnd(d1) - X * cnd(d2));
	}
    else { /* Receiver swaption */
        result 
			= ((1.0 - 1.0 / pow((1.0 + F / m), (t1 * m))) / F) 
			* exp(-r * T) * (X * cnd(-d2) - F * cnd(-d1));
	}

	assert(is_sane(result));
	return result;
}

#ifdef SWAPOPTION_CHECK
void check_Swapoption(void)
{
	double t1 = 4, m = 2, F = 0.07, X = 0.075, T = 2, r = 0.06, v = 0.20;
	double fasit = 1.7964 / 100.0;
	
	double result = Swapoption(1, t1, m, F, X, T, r, v);
	assert_equal(result, fasit);
}


int main(void)
{
	check_Swapoption();
	return 0;
}
#endif

