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

/* Calculation of critical price options on options */
static double CriticalValueOptionsOnOptions(
	int fCall,
	double X1,
	double X2,
	double T, 
	double r,
	double b,
	double v) 
{
	double Si, ci, di, epsilon = 0.000001;
        int counter = 0;

	assert_valid_strike(X1);
	assert_valid_strike(X2);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    Si = X1;
    ci = gbs(fCall, Si, X1, T, r, b, v);
    di = delta(fCall, Si, X1, T, r, b, v);

    /* Newton-Raphson algorithm */
    while(fabs(ci - X2) > epsilon) {
        Si = Si - (ci - X2) / di;
        ci = gbs(fCall, Si, X1, T, r, b, v);
        di = delta(fCall, Si, X1, T, r, b, v);

        if( counter++ >= 100 )
          return 0;
    }

    return Si;
}

/* Options on options */
double OptionsOnOptions(
	int typeflag,
	double S,
	double X1,
	double X2,
	double t1, 
	double T2,
	double r,
	double b,
	double v) 
{
	double result, bv2, vst1, vsT2, I, Rho, _y1, y2, z1, z2;
	int fCall;

	assert_valid_price(S);
	assert_valid_strike(X1);
	assert_valid_strike(X2);
	assert_valid_time(t1);
	assert_valid_time(T2);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	bv2 = b + pow2(v) / 2.0;
	vst1 = v * sqrt(t1);
	vsT2 = v * sqrt(T2);

	assert(typeflag == OOO_CALL_ON_CALL || typeflag == OOO_CALL_ON_PUT || typeflag == OOO_PUT_ON_CALL || typeflag == OOO_PUT_ON_PUT);
    
	if(typeflag == OOO_CALL_ON_CALL || typeflag == OOO_PUT_ON_CALL)
        fCall = 1;
    else
        fCall = 0;
    
    I = CriticalValueOptionsOnOptions(fCall, X1, X2, T2 - t1, r, b, v);
    
    Rho = sqrt(t1 / T2);
    _y1 = (log(S / I) + bv2 * t1) / vst1;
    y2 = _y1 - vst1;
    z1 = (log(S / X1) + bv2 * T2) / vsT2;
    z2 = z1 - vsT2;

	if(typeflag == OOO_CALL_ON_CALL) {
        result 
			=  S * exp((b - r) * T2) * cbnd(z1, _y1, Rho) 
			- X1 * exp(-r * T2)      * cbnd(z2, y2, Rho) 
			- X2 * exp(-r * t1)      * cnd(y2);
    }
	else if(typeflag == OOO_PUT_ON_CALL) {
        result 
			= X1 * exp(-r * T2)      * cbnd(z2, -y2, -Rho) 
			-  S * exp((b - r) * T2) * cbnd(z1, -_y1, -Rho) 
			+ X2 * exp(-r * t1)      * cnd(-y2);
    }
	else if(typeflag == OOO_CALL_ON_PUT) {
        result 
			= X1 * exp(-r * T2)      * cbnd(-z2, -y2, Rho) 
			-  S * exp((b - r) * T2) * cbnd(-z1, -_y1, Rho) 
			- X2 * exp(-r * t1)      * cnd(-y2);
    }
	else if(typeflag == OOO_PUT_ON_PUT) {
        result 
			=  S * exp((b - r) * T2) * cbnd(-z1, _y1, -Rho) 
			- X1 * exp(-r * T2)      * cbnd(-z2, y2, -Rho) 
			+ X2 * exp(-r * t1)      * cnd(y2);
    }
	else {
		/* Abort to be on the safe side */
		abort();
	}

	assert(is_sane(result));
	return result;
}

#ifdef OPTIONSONOPTIONS_CHECK

void check_OptionsOnOptions(void)
{
	/* Put on Call, options on options. */
	double S = 500.0, X1 = 520.0, X2 = 50.0, t1 = 0.25, T2 = 0.5, r = 0.08, b = 0.05, v = 0.35;

	assert_equal(OptionsOnOptions(OOO_PUT_ON_CALL, S, X1, X2, t1, T2, r, b, v), 21.1965);
}

int main(void)
{
	check_OptionsOnOptions();
	return 0;
}
#endif

