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


/* Takeover foreign exchange options */
double TakeoverFXoption(
	double v,
	double b,
	double E,
	double X,
	double T,
	double r,
	double rf,
	double vV,
	double vE,
	double Rho) 
{
	double sT, a1, a2, result;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(vV);
	assert_valid_volatility(vE);

	sT = sqrt(T);
    a1 = (log(v / b) + (rf - Rho * vE * vV - pow2(vV) / 2.0) * T) / (vV * sT);
    a2 = (log(E / X) + (r - rf - pow2(vE) / 2.0) * T) / (vE * sT);
    
    result 
		= b * (
			  E * exp(-rf * T) * cbnd(a2 + vE * sT, -a1 - Rho * vE * sT, -Rho) 
			- X * exp(-r * T)  * cbnd(-a1, a2, -Rho)
		); 

	assert(is_sane(result));
	return result;
}

#ifdef TAKEOVERFXOPTION_CHECK
void check_TakeoverFXoption(void)
{
}

int main(void)
{

	check_TakeoverFXoption();
	return 77;
}
#endif

