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
#include <stdio.h>
#include <assert.h>

#include "metaoptions.h"

/* Performance notes:
 * Calls/sec	Action
 * 189.000		Making phi() an inlineable function
 * 189.000		Replaced pow2(v) with a vv variable in phi().
 * 189.000		Replaced pow2(v) with a vv variable in BSAmericanCallApprox().
 * 189.000		Hmm, 6 out of 8 params to phi() are always the same(S,T,I,r,b and v). Can we precompute them? Nope...
 */

/* Newton Raphson algorithm to solve for the critical 
 * commodity price for a Call 
 */
static double
phi(double S, double T, double gamma_val, double H, double I, double r, double b, double v) 
{
	double vst, vv, lambda, d, kappa;

	assert_valid_price(S);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
	vv = v * v;

    lambda = (-r + gamma_val * b + 0.5 * gamma_val * (gamma_val - 1.0) * vv) * T;
    d = -(log(S / H) + (b + (gamma_val - 0.5) * vv) * T) / vst;
    kappa = 2.0 * b / vv + (2.0 * gamma_val - 1.0);

    return exp(lambda) 
		* pow(S, gamma_val)
		* (cnd(d) - pow(I / S, kappa) * cnd(d - 2.0 * log(I / S) / vst));
}

double BSAmericanCallApprox(double S, double X, double T, double r, double b, double v) 
{
	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

    if(b >= r ) {
		/* Never optimal to exercise before maturity */
		return gbs_call(S, X, T, r, b, v);
	}
    else {
		double vv, Beta, BInfinity, B0, ht, I;
		
		vv = v*v;
		assert(is_sane(vv));

        Beta = (0.5 - b / vv) + sqrt(pow2(b / vv - 0.5) + 2.0 * r / vv);
		assert(is_sane(Beta));

        BInfinity = Beta / (Beta - 1.0) * X;
		assert(is_sane(BInfinity));

        B0 = fmax(X, r / (r - b) * X);
		assert(is_sane(B0));

        ht = -(b * T + 2.0 * v * sqrt(T)) * B0 / (BInfinity - B0);
		assert(is_sane(ht));

        I = B0 + (BInfinity - B0) * (1.0 - exp(ht));
		assert(is_sane(I));

        if(S >= I )
            return S - X;
        else {
			const double alpha = (I - X) * pow(I, -Beta);

            return alpha * pow(S, Beta)
				- alpha * phi(S, T, Beta, I, I, r, b, v) 
				+ phi(S, T, 1.0,  I, I, r, b, v) 
				- phi(S, T, 1.0,  X, I, r, b, v) 
				- X * phi(S, T, 0.0,  I, I, r, b, v) 
				+ X * phi(S, T, 0.0,  X, I, r, b, v);
		}
    }
}

double BSAmericanApprox(int fCall, double S, double X, double T, double r, double b, double v) 
{
	double result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

    if(fCall)
        result = BSAmericanCallApprox(S, X, T, r, b, v);
    else {
		/* Use the Bjerksund and Stensland put-call transformation */
        result = BSAmericanCallApprox(X, S, T, r - b, -b, v);
	}
    
	assert(is_sane(result));
	return result;
}

#ifdef BSAMERICANAPPROX_CHECK
/* Bjerksund & Stensland Approximation, page 26 */
void check_BSAmericanApprox(void)
{ 
	double S = 42.0, X = 40.0, T = 0.75, r = 0.04, b = -0.04, v = 0.35;

	double computed = BSAmericanApprox(1, S, X, T, r, b, v);
	assert_equal(computed, 5.2704);

	computed = BSAmericanCallApprox(S, X, T, r, b, v);
	assert_equal(computed, 5.2704);
}
int main(void)
{
	check_BSAmericanApprox();
	printf("Mangler data for puts\n");
	return 0;
}

#endif

