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

/* American Calls on stocks with known dividends, Roll-Geske-Whaley */
double RollGeskeWhaley(
	double S,
	double X,
	double t1,
	double T2,
	double r,
	double d,
	double v) 
{
	double Sx, result;
    const double xinfinity = 100000000.0;
    const double epsilon = 0.00001;

	double ci, HighS, LowS, I;
	double vst1, vst2, a1, a2, b1, b2;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(t1);
	assert_valid_time(T2);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);


	/* The expiry date of the option must be after the dividend payment date */
	assert(T2 > t1);
    
    Sx = S - d * exp(-r * t1);
    if(d <= X * (1.0 - exp(-r * (T2 - t1))) ) { 
		/* Not optimal to exercise */
        result = blackscholes(1, Sx, X, T2, r, v);
        return result;
    }


    ci = blackscholes_call(S, X, T2 - t1, r, v);
    HighS = S;
    while((ci - HighS - d + X) > 0 && HighS < xinfinity) {
        HighS = HighS * 2.0;
        ci = blackscholes(1, HighS, X, T2 - t1, r, v);
    }

    if(HighS > xinfinity ) {
        result = blackscholes_call(Sx, X, T2, r, v);
        return result;
    }
    
    LowS = 0.0;
    I = HighS * 0.5;
    ci = blackscholes(1, I, X, T2 - t1, r, v);
    
    /* Search algorithm to find the critical stock price I */
    while(fabs(ci - I - d + X) > epsilon && (HighS - LowS) > epsilon ) {
        if((ci - I - d + X) < 0 )
            HighS = I;
        else
            LowS = I;
        
        I = (HighS + LowS) / 2.0;
        ci = blackscholes(1, I, X, T2 - t1, r, v);
    }

	vst1 = v * sqrt(t1);
	vst2 = v * sqrt(T2);

    a1 = (log(Sx / X) + (r + pow2(v) / 2.0) * T2) / vst2;
    a2 = a1 - vst2;
    b1 = (log(Sx / I) + (r + pow2(v) / 2.0) * t1) / vst1;
    b2 = b1 - vst1;
   
    result 
		= Sx * cnd(b1) 
		+ Sx * cbnd(a1, -b1, -sqrt(t1 / T2)) 
		- X * exp(-r * T2) * cbnd(a2, -b2, -sqrt(t1 / T2)) 
		- (X - d) * exp(-r * t1) * cnd(b2);

	assert(is_sane(result));
	return result;
}

#ifdef ROLLGESKEWHALEY_CHECK

void check_RollGeskeWhaley(void)
{
	/* RollGeskeWhaley is used for American calls on stocks with known 
	 * dividends. It computes the value of a call. 
	 */
	double S = 80.0;
	double X = 82;
	double t1 = 3.0 /12;	/* Time to expiration. */
	double T2 = 4.0 / 12; /* Time to dividend is paid */
	double D = 4.0; /* Dividend paid */
	double r = 0.06;
	double v = 0.30; 
	assert_equal(RollGeskeWhaley(S, X, t1, T2, r, D, v), 4.3860);
}


int main(void)
{
	check_RollGeskeWhaley();
	return 0;
}
#endif

