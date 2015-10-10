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

#include "metaoptions.h"
#include <math.h>
/* Optimizations:
 * Calls/sec	Action
 * 171.000		Using gvega_inlined() instead of vega()
 * 177.000		Removed call to blackscholes() in test program 
 * 196.000		Calling NewtonRaphson_call() and _put().
 * 377.000		Quite impressive, can it be correct? Making the _put/call() versions inline.
 * 395.000      A slight improvement, but is it worth it? Nope, we rollback the changes.
 * 377.000		Making epsilon a static const common to all functions in this file.
 * 385.000		Removing the algo from NewtonRaphson(), we don't need three versions of it...
 */

static const double epsilon = 0.00000000001;
int NewtonRaphson(int fCall, double S, double X, double T, double r, double cm, double *piv)
{
	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);

	if(fCall)
		return NewtonRaphson_call(S, X, T, r, cm, piv);
	else
		return NewtonRaphson_put(S, X, T, r, cm, piv);
}

/*
 * TODO(20070506 boa):
 * This function (and its _put buddy) is broken by design. If cm(aka price)
 * is outside sane limits, vi (Vol Implied) goes < 0.0. 
 * The functions gbs() and vega() * don't appreciate such input.
 * We must figure out a way to handle this, avoiding an eternal loop.
 */
int NewtonRaphson_call(double S, double X, double T, double r, double cm, double *piv)
{
	double vi, ci, vegai;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);

	/* Compute the Manaster and Koehler seed value (vi) */
	vi = sqrt(fabs(log(S/X) + r * T) * 2.0/T);
	ci = gbs_call(S, X, T, r, r, vi);
	vegai = vega(S, X, T, r, r, vi);

	while(fabs(cm - ci) > epsilon) {
		vi -= (ci - cm)/vegai;
		if(vi < VOLATILITY_MIN || vi > VOLATILITY_MAX)
			return 0;

		ci = gbs_call(S, X, T, r, r, vi);
		vegai = vega(S, X, T, r, r, vi);
	}

	*piv = vi;
	return 1;
}

int NewtonRaphson_put(double S, double X, double T, double r, double cm, double *piv)
{
	double vi, ci, vegai;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);

	/* Compute the Manaster and Koehler seed value (vi) */
	vi = sqrt(fabs(log(S/X) + r * T) * 2.0/T);
	ci = gbs_put(S, X, T, r, r, vi);
	vegai = vega(S, X, T, r, r, vi);

	while(fabs(cm - ci) > epsilon) {
		vi -= (ci - cm)/vegai;
		if(vi < VOLATILITY_MIN || vi > VOLATILITY_MAX)
			return 0;

		ci = gbs_put(S, X, T, r, r, vi);
		vegai = vega(S, X, T, r, r, vi);
	}

	*piv = vi;
	return 1;
}

#ifdef NEWTONRAPHSON_CHECK
/*
 * We use NewtonRaphson() to compute the iv of an european option.
 * How do we test it? We use one of the other functions to compute
 * the value of an option, given a v. Then we feed the price into
 * NewtonRaphson() and see if the returned iv is OK.
 */
void check_NewtonRaphson(void)
{
	int fCall = 1, ok;
	double iv, S = 100.0, X = 100.0, T = 0.5, r = 0.08, v = 0.20;

	double cm = blackscholes(fCall, S, X, T, r, v);
	ok = NewtonRaphson(fCall, S, X, T, r, cm, &iv);
	assert(ok);
	assert_equal(v, iv);

	fCall = 0;
	cm = blackscholes(fCall, S, X, T, r, v);
	ok = NewtonRaphson(fCall, S, X, T, r, cm, &iv);
	assert(ok);
	assert_equal(v, iv);
}

/* WTF??? Two functions? */

/* NewtonRhapson for imp. vol of european options */
void check_NewtonRaphson_put(void)
{
	int fCall = 0, ok;

	double S = 75.0, X = 70.0, T = 0.5, r = 0.10,  v = 0.35;

	double computed, price = gbs(fCall, S, X, T, r, r, v);
	ok = NewtonRaphson(fCall, S, X, T, r, price, &computed);
	assert(ok);
	assert_equal(computed, v);

	ok = NewtonRaphson_put(S, X, T, r, price, &computed);
	assert(ok);
	assert_equal(computed, v);
}


int main(void)
{
	check_NewtonRaphson();
	check_NewtonRaphson_put();
	return 0;
}
#endif

