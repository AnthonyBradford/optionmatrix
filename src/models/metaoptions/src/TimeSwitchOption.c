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
#include <stdio.h>

#include "metaoptions.h"


/* Time switch options (discrete) */
double TimeSwitchOption(
	int fCall,
	double S,
	double X,
	double a,
	double T,
	int m ,
	double dt,
	double r,
	double b,
	double v) 
{
    int i, Z, n;
	double logSX, vv, erT, sum;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    if (fCall) 
        Z = 1;
	else
        Z = -1;

	{ /* Workaround for compiler 'bug' on x86 */
		double tmp = T / dt;
		n = (int)tmp;
	}

	logSX = log(S/X);
	vv = v*v;
	erT = exp(-r * T);

    sum = 0;
	for(i = 1; i <= n; i++) {
        double d = (logSX + (b - vv / 2.0) * i * dt) / (v * sqrt(i * dt));
        sum += cnd(Z * d) * dt;
    }

    return (a * erT * sum) + (dt * a * erT * m);
}

#ifdef TIMESWITCHOPTION_CHECK

/* page 37-39 */
void check_TimeSwitchOption(void)
{
	double S = 100.0, A = 5.0, X = 110.0, T = 1.0, dt = 1.0/365.0, r = 0.06, b = r, v = 0.26;
	int m = 0;
	double result, fasit = 1.3750;
	fprintf(stderr, "dt:%.20f 1.0/(1.0/365.0):%d\n", dt, (int)(1.0 / (1.0/365.0)));
	result = TimeSwitchOption(1, S, X, A, T, m, dt, r, b, v);
	assert_equal(result, fasit);
}


int main(void)
{
	check_TimeSwitchOption();
	return 0;
}
#endif

