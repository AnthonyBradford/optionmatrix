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
#include <stdlib.h>

#include "metaoptions.h"

static double CriticalPart2(
	int id,
	double I,
	double t1,
	double T2,
	double v) 
{
	double result;

    if (id == 1) {
        const double z1 = (log(I) + pow2(v) / 2.0 * (T2 - t1)) / (v * sqrt(T2 - t1));
        result = cnd(z1);
    }
	else if(id == 2) {
        const double z2 = (-log(I) - pow2(v) / 2.0 * (T2 - t1)) / (v * sqrt(T2 - t1));
        result = -cnd(z2);
    }
	else 
		abort();

	return result;
}

static double CriticalPart3(
	int id,
	double I,
	double t1,
	double T2,
	double v) 
{
	double result;

    double z1, z2;
	const double vT2_t1 = v * sqrt(T2 - t1);
	const double p2v = pow2(v);
	const double logI = log(I);

    if (id == 1) {
        z1 = (logI + p2v / 2.0 * (T2 - t1)) / vT2_t1;
        z2 = (logI - p2v / 2.0 * (T2 - t1)) / vT2_t1;
        result = I * cnd(z1) - cnd(z2);
    }
	else if( id == 2) {
        z1 = (-logI + pow2(v) / 2.0 * (T2 - t1)) / vT2_t1;
        z2 = (-logI - pow2(v) / 2.0 * (T2 - t1)) / vT2_t1;
        result = cnd(z1) - I * cnd(z2);
    }
	else 
		abort();

	return result;
}


/* Numerical search algorithm to find critical price I */
static double CriticalPrice(
	int id,
	double I1,
	double t1,
	double T2,
	double v,
	double q) 
{
	double result;

    double Ii = I1;
    double yi = CriticalPart3(id, Ii, t1, T2, v);
    double di = CriticalPart2(id, Ii, t1, T2, v);
    const double epsilon = 0.00001;
    while(fabs(yi - q) > epsilon) {
        Ii = Ii - (yi - q) / di;
        yi = CriticalPart3(id, Ii, t1, T2, v);
        di = CriticalPart2(id, Ii, t1, T2, v);
    }

    result = Ii;
	return result;
}


/* Exchange options on exchange options */
double ExchangeExchangeOption(
	int TypeFlag,
	double S1,
	double S2,
	double q,
	double t1,
	double T2,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho) 
{
	double result, I, d1, d2, d3, d4, Y1, y2, y3, y4;
	double st1T2, v, I1;
	int id;

	/* TODO: No asserts 20070310 */
	st1T2 = sqrt(t1 / T2);
    v = sqrt(pow2(v1) + pow2(v2) - 2.0 * Rho * v1 * v2);
    I1 = S1 * exp((b1 - r) * (T2 - t1)) / (S2 * exp((b2 - r) * (T2 - t1)));
    
	if (TypeFlag == 1 || TypeFlag == 2) 
        id = 1;
    else
        id = 2;
    
    I = CriticalPrice(id, I1, t1, T2, v, q);
    d1 = (log(S1 / (I * S2)) + (b1 - b2 + pow2(v) / 2.0) * t1) / (v * sqrt(t1));
    d2 = d1 - v * sqrt(t1);
    d3 = (log((I * S2) / S1) + (b2 - b1 + pow2(v) / 2.0) * t1) / (v * sqrt(t1));
    d4 = d3 - v * sqrt(t1);

    Y1 = (log(S1 / S2) + (b1 - b2 + pow2(v) / 2.0) * T2) / (v * sqrt(T2));
    y2 = Y1 - v * sqrt(T2);
    y3 = (log(S2 / S1) + (b2 - b1 + pow2(v) / 2.0) * T2) / (v * sqrt(T2));
    y4 = y3 - v * sqrt(T2);
    
    if (TypeFlag == 1) {
        result 
			= -S2 
			* exp((b2 - r) * T2) 
			* cbnd(d2, y2, st1T2) 
			+ S1 
			* exp((b1 - r) * T2) 
			* cbnd(d1, Y1, st1T2) 
			- q 
			* S2 
			* exp((b2 - r) * t1) 
			* cnd(d2);
    }
	else if( TypeFlag == 2) {
        result 
			= S2 
			* exp((b2 - r) * T2) 
			* cbnd(d3, y2, -st1T2) - S1 
			* exp((b1 - r) * T2) 
			* cbnd(d4, Y1, -st1T2) + q 
			* S2 
			* exp((b2 - r) * t1) 
			* cnd(d3);
    }
	else if( TypeFlag == 3) {
        result 
			= S2 
			* exp((b2 - r) * T2) 
			* cbnd(d3, y3, st1T2) - S1 
			* exp((b1 - r) * T2) 
			* cbnd(d4, y4, st1T2) - q 
			* S2 
			* exp((b2 - r) * t1) 
			* cnd(d3);
    }
	else if( TypeFlag == 4) {
        result 
			= -S2 
			* exp((b2 - r) * T2) 
			* cbnd(d2, y3, -st1T2) + S1 
			* exp((b1 - r) * T2) 
			* cbnd(d1, y4, -st1T2) + q 
			* S2 
			* exp((b2 - r) * t1) 
			* cnd(d2);
    }
	else
		abort();

	return result;
}

#ifdef EXCHANGEEXCHANGEOPTION_CHECK

/* Page 54-56 */
void check_ExchangeExchangeOption(void)
{
	double S2 = 100, t1 = 0.75, T2 = 1.0, r = 0.10, b1 = 0.10, b2 = 0.10, Q = 0.10;

	struct entry {
		double s1_100, s1_105;
	};
		
	/* Lots of test values from page 56 */
	static struct {
		int typeflag; 
		double v1, v2; /* Two volatility values */
		/* We have values for Rho -0,5, 0, 0.5 */
		struct entry values[3]; 
	} val[] = {
		{ 1, 0.20, 0.20, { { 8.5403, 10.9076}, {6.2333, 8.4333}, {3.3923, 5.2802}}},
		{ 1, 0.20, 0.25, { {10.1756, 12.6391}, {7.5787, 9.8819}, {4.3605, 6.3758}}},
		{ 1, 0.25, 0.20, { {10.1756, 12.6391}, {7.5787, 9.8819}, {4.3605, 6.3758}}},

		{ 2, 0.20, 0.20, { { 4.7893,  4.1747}, {4.9870, 4.2359}, {5.4267, 4.3746}}},
		{ 2, 0.20, 0.25, { { 4.6948,  4.1492}, {4.8607, 4.1961}, {5.2395, 4.3166}}},
		{ 2, 0.25, 0.20, { { 4.6948,  4.1492}, {4.8607, 4.1961}, {5.2395, 4.3166}}},

		{ 3, 0.20, 0.20, { { 7.3679,  5.9428}, {5.3005, 3.9927}, {2.7895, 1.7663}}},
		{ 3, 0.20, 0.25, { { 8.8426,  7.3670}, {6.5040, 5.1199}, {3.6392, 2.4929}}},
		{ 3, 0.25, 0.20, { { 8.8426,  7.3670}, {6.5040, 5.1199}, {3.6392, 2.4929}}},

		{ 4, 0.20, 0.20, { { 3.6169,  4.2099}, {4.0542, 4.7954}, {4.8239, 5.8607}}},
		{ 4, 0.20, 0.25, { { 3.3619,  3.8771}, {3.7859, 4.4341}, {4.5182, 5.4337}}},
		{ 4, 0.25, 0.20, { { 3.3619,  3.8771}, {3.7859, 4.4341}, {4.5182, 5.4337}}},
	};

	size_t i, j, nelem = sizeof(val) / sizeof(val[0]);

	for(i = 0; i < nelem; i++) {
		double res100, res105, Rho;

		for(j = 0, Rho = -0.5; j < 3; j++, Rho += 0.5) {
			res100 = ExchangeExchangeOption(val[i].typeflag, 100, S2, Q, t1, T2, r, b1, b2, val[i].v1, val[i].v2, Rho);
			res105 = ExchangeExchangeOption(val[i].typeflag, 105, S2, Q, t1, T2, r, b1, b2, val[i].v1, val[i].v2, Rho);
			assert_equal(val[i].values[j].s1_100, res100);
			assert_equal(val[i].values[j].s1_105, res105);
		}
	}
}

int main(void)
{
	check_ExchangeExchangeOption();
	return 0;
}
#endif

