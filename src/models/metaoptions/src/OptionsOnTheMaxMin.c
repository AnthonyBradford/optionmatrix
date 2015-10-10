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
#include <string.h>
#include <assert.h>

#include "metaoptions.h"


/* Options on the maximum or minimum of two risky assets */
double OptionsOnTheMaxMin(
	const char* TypeFlag,
	double S1,
	double S2,
	double X,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho) 
{
	double sT, v, rho1, rho2, d, _y1, y2, result;

	assert_valid_price(S1);
	assert_valid_price(S2);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b1);
	assert_valid_cost_of_carry(b2);
	assert_valid_volatility(v1);
	assert_valid_volatility(v2);


	sT = sqrt(T);
    v = sqrt(pow2(v1) + pow2(v2) - 2.0 * Rho * v1 * v2);
    rho1 = (v1 - Rho * v2) / v;
    rho2 = (v2 - Rho * v1) / v;
    d  = (log(S1 / S2) + (b1 - b2 + pow2(v)  / 2.0) * T) / (v * sT);
    _y1 = (log(S1 / X)  + (b1      + pow2(v1) / 2.0) * T) / (v1 * sT);
    y2 = (log(S2 / X)  + (b2      + pow2(v2) / 2.0) * T) / (v2 * sT);
  
    if (!strcmp(TypeFlag, "cmin")) {
        result 
			= S1 * exp((b1 - r) * T) * cbnd(_y1, -d, -rho1) 
			+ S2 * exp((b2 - r) * T) * cbnd(y2, d - v * sT, -rho2) 
			- X  * exp(-r * T)       * cbnd(_y1 - v1 * sT, y2 - v2 * sT, Rho);
    }
	else if( !strcmp(TypeFlag, "cmax")) {
        result 
			= S1 * exp((b1 - r) * T) * cbnd(_y1, d, rho1) 
			+ S2 * exp((b2 - r) * T) * cbnd(y2, -d + v * sT, rho2) 
			- X  * exp(-r * T)       * (1.0 - cbnd(-_y1 + v1 * sT, -y2 + v2 * sT, Rho));
    }
	else if( !strcmp(TypeFlag, "pmin")) {
        result 
			= X * exp(-r * T) - S1 * exp((b1 - r) * T) 
			+ EuropeanExchangeOption(S1, S2, 1.0, 1.0, T, r, b1, b2, v1, v2, Rho) 
			+ OptionsOnTheMaxMin("cmin", S1, S2, X, T, r, b1, b2, v1, v2, Rho);
    }
	else if( !strcmp(TypeFlag, "pmax" )){
        result 
			= X * exp(-r * T) - S2 * exp((b2 - r) * T) 
			- EuropeanExchangeOption(S1, S2, 1.0, 1.0, T, r, b1, b2, v1, v2, Rho) 
			+ OptionsOnTheMaxMin("cmax", S1, S2, X, T, r, b1, b2, v1, v2, Rho);
    }
	else
		abort();

	assert(is_sane(result));
	return result;
}

#ifdef OPTIONSONTHEMAXMIN_CHECK
void check_OptionsOnTheMaxMin(void)
{
	printf("%s(): Not implemented\n", __func__);
}

int main(void)
{
	check_OptionsOnTheMaxMin();
	return 77;
}
#endif

