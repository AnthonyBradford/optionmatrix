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
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "metaoptions.h"

/* Performance notes.
 * Calls/sec	Action
 *  31.000		Minor cleanup
 *  31.000		Making typeflag an int
 *  31.000		Replacing if/elseif with switch and removing the variable named result.
 *  25.424		New and slower laptop machine
 *  25.000		Changed a couple of literals from e.g. 2 to 2.0
 *  11.500		WTF?
 */

/* Double barrier options */
double DoubleBarrier(
	int typeflag,
	double S,
	double X,
	double L,
	double U,
	double T,
	double r,
	double b,
	double v,
	double delta1,
	double delta2) 
{
	int n;

	double vst, p2v, F, E, dd, LS;
    double outval, Sum1 = 0, Sum2 = 0;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	vst = v * sqrt(T);
	p2v = pow2(v);
    
    F = U * exp(delta1 * T);
    E = L * exp(delta2 * T);
	dd = delta1 - delta2;
	LS = L / S;

    if(typeflag == DB_CALL_OUT || typeflag == DB_CALL_IN) { 
        for(n = -5; n <= 5; n++) {
			double powL2n = pow(L, (2.0 * n));
			double SpowU2n = S * pow(U, (2.0 * n));
			double powLn = pow(L, n);
			double powUn = pow(U, n);
			double bp2v2T = (b + p2v / 2.0) * T;

            double d1 = (log(SpowU2n / (X * powL2n)) + bp2v2T) / vst;
            double d2 = (log(SpowU2n / (F * powL2n)) + bp2v2T) / vst;
            double d3 = (log(pow(L, (2.0 * n + 2.0)) / (X * SpowU2n)) + bp2v2T) / vst;
            double d4 = (log(pow(L, (2.0 * n + 2.0)) / (F * SpowU2n)) + bp2v2T) / vst;

            double mu1 = 2.0 * (b - delta2 - n * dd) / p2v + 1.0;
            double mu2 = 2.0 * n * dd / p2v;
            double mu3 = 2.0 * (b - delta2 + n * dd) / p2v + 1.0;

            Sum1 += pow(powUn / powLn, mu1) * pow(LS, mu2) * (cnd(d1) - cnd(d2)) 
				- pow((pow(L, (n + 1.0)) / (powUn * S)), mu3) * (cnd(d3) - cnd(d4));

            Sum2 += pow(powUn / powLn, (mu1 - 2.0)) * pow(LS, mu2) * (cnd(d1 - vst) - cnd(d2 - vst)) 
				- pow((pow(L, (n + 1.0)) / (powUn * S)), (mu3 - 2.0)) * (cnd(d3 - vst) - cnd(d4 - vst));
        }

        outval = S * exp((b - r) * T) * Sum1 - X * exp(-r * T) * Sum2;
    }
	else if(typeflag == DB_PUT_IN || typeflag == DB_PUT_OUT) {
        for(n = -5; n <= 5; n++) {
			double powL2n = pow(L, 2.0 * n);
			double SpowU2n = S * pow(U, 2.0 * n);
			double powLn = pow(L, n);
			double powUn = pow(U, n);
			double bp2v2T = (b + p2v / 2.0) * T;

            double d1 = (log(SpowU2n / (E * powL2n)) + bp2v2T) / vst;
            double d2 = (log(SpowU2n / (X * powL2n)) + bp2v2T) / vst;
            double d3 = (log(pow(L, (2.0 * n + 2.0)) / (E * SpowU2n)) + bp2v2T) / vst;
            double d4 = (log(pow(L, (2.0 * n + 2.0)) / (X * SpowU2n)) + bp2v2T) / vst;

            double mu1 = 2.0 * (b - delta2 - n * dd) / p2v + 1.0;
            double mu2 = 2.0 * n * dd / p2v;
            double mu3 = 2.0 * (b - delta2 + n * dd) / p2v + 1.0;

            Sum1 += pow(powUn / powLn, mu1) * pow(LS, mu2) * (cnd(d1) - cnd(d2))
				 - pow((pow(L, n + 1.0) / (powUn * S)), mu3) * (cnd(d3) - cnd(d4));

            Sum2 += pow(powUn / powLn, (mu1 - 2.0)) * pow(LS, mu2) * (cnd(d1 - vst) - cnd(d2 - vst))
				- pow((pow(L, n + 1.0) / (powUn * S)), (mu3 - 2.0)) * (cnd(d3 - vst) - cnd(d4 - vst));
        }

        outval = X * exp(-r * T) * Sum2 - S * exp((b - r) * T) * Sum1;
    }
	else
		abort();

	switch(typeflag) {
		case DB_CALL_OUT:
		case DB_PUT_OUT: return outval;
        case DB_CALL_IN: return gbs_call(S, X, T, r, b, v) - outval;
		case DB_PUT_IN: return gbs_put(S, X, T, r, b, v) - outval;
    	default: abort();
	}
}

#ifdef DOUBLEBARRIER_CHECK
/* Page 72-76 */
static void check_DoubleBarrier(void)
{
	int typeflag = DB_CALL_OUT;
	double S = 100.0, X = 100.0, r = 0.10, b = 0.10;

	/* The table 2-10 contains a massive amount of test data, 
	 * 72 values for different combinations of T,v,L,U, delta1 and delta2.
	 */
	struct {
		double L, U, d1, d2;
		double fasit[2][3];
	} values[15] = {
		{ 50, 150, 0, 0,      { {4.3515, 6.1644, 7.0373}, {6.9853, 7.9336, 6.5088}}},
		{ 60, 140, 0, 0,      { {4.3505, 5.8500, 5.7726}, {6.8082, 6.3383, 4.3841}}},
		{ 70, 130, 0, 0,      { {4.3139, 4.8293, 3.7765}, {5.9697, 4.0004, 2.2563}}},
		{ 80, 120, 0, 0,      { {3.7516, 2.6387, 1.4903}, {3.5805, 1.5098, 0.5635}}},
		{ 90, 110, 0, 0,      { {1.2055, 0.3098, 0.0477}, {0.5537, 0.0441, 0.0011}}},

		{ 50, 150, -0.1, 0.1, { {4.3514, 6.0997, 6.6987}, {6.8974, 6.9821, 5.2107}}},
		{ 60, 140, -0.1, 0.1, { {4.3478, 5.6351, 5.2463}, {6.4094, 5.0199, 3.1503}}},
		{ 70, 130, -0.1, 0.1, { {4.2558, 4.3291, 3.1540}, {4.8182, 2.6259, 1.3424}}},
		{ 80, 120, -0.1, 0.1, { {3.2953, 1.9868, 1.0351}, {1.9245, 0.6455, 0.1817}}},
		{ 90, 110, -0.1, 0.1, { {0.5887, 0.1016, 0.0085}, {0.0398, 0.0002, 0.0000}}},

		{ 50, 150, 0.1, -0.1, { {4.3515, 6.2040, 7.3151}, {7.0086, 8.6080, 7.7218}}},
		{ 60, 140, 0.1, -0.1, { {4.3512, 5.9998, 6.2395}, {6.9572, 7.4267, 5.6620}}},
		{ 70, 130, 0.1, -0.1, { {4.3382, 5.2358, 4.3859}, {6.6058, 5.3761, 3.3446}}},
		{ 80, 120, 0.1, -0.1, { {4.0428, 3.2872, 2.0048}, {5.0718, 2.6591, 1.1871}}},
		{ 90, 110, 0.1, -0.1, { {1.9229, 0.6451, 0.1441}, {1.7079, 0.3038, 0.0255}}}

		/* Man, it was boring to write all those numbers :-(( */
	};

	size_t i, nelem = sizeof(values) / sizeof(values[0]);
	assert(nelem == 15);

	for(i = 0; i < nelem; i++) {
		size_t iT;
		double T;
		for(iT = 0, T = 0.25; iT < 2; iT++, T += 0.25) {
			size_t iv;
			double v;
			for(iv = 0, v = 0.15; iv < 3; iv++, v += 0.10) {
				double res, fasit = values[i].fasit[iT][iv];
				res = DoubleBarrier(typeflag, S, X, values[i].L, values[i].U, T, r, b, v, values[i].d1, values[i].d2);
				assert_equal(res, fasit);
			}
		}
	}
}


int main(void)
{
	check_DoubleBarrier();
	return 0;
}

#endif

