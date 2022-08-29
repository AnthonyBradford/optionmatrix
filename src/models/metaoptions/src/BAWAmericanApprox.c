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

static double Kp(
	double X,
	double T,
	double r,
	double b,
	double v) 
{
	double st, vst, p2v, n, m, q1u, Su, h1, Si, K, d1, cndd1, Q1, LHS, ebrt, RHS, bi, E;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);


	st = sqrt(T);
	vst = v * st;
	p2v = pow2(v);

	/* Calculation of seed value, Si */
	n = 2.0 * b / p2v;
	m = 2.0 * r / p2v;
	q1u = (-(n - 1) - sqrt(pow2(n - 1) + 4 * m)) / 2.0;
	Su = X / (1.0 - 1.0 / q1u);
	h1 = (b * T - 2.0 * vst) * X / (X - Su);
	Si = Su + (X - Su) * exp(h1);
    
	K = 2.0 * r / (p2v * (1.0 - exp(-r * T)));
	d1 = (log(Si / X) + (b + p2v / 2.0) * T) / vst;
	cndd1 = cnd(-d1);
	Q1 = (-(n - 1.0) - sqrt(pow2(n - 1.0) + 4.0 * K)) / 2.0;
	LHS = X - Si;

	ebrt = exp((b - r) * T);
	RHS = gbs_put(Si, X, T, r, b, v) - (1.0 - ebrt * cndd1) * Si / Q1;

	bi = -ebrt * cndd1 * (1.0 - 1.0 / Q1) - (1.0 + ebrt * normdist(-d1) / vst) / Q1;
	E = 0.000001;

	/* Newton Raphson algorithm for finding critical price Si */
	while(fabs(LHS - RHS) / X > E) {
	  Si = (X - RHS + bi * Si) / (1.0 + bi);
	  d1 = (log(Si / X) + (b + p2v / 2.0) * T) / vst;
	  cndd1 = cnd(-d1);
	  LHS = X - Si;
	  ebrt = exp((b - r) * T);
	  RHS = gbs_put(Si, X, T, r, b, v) - (1.0 - ebrt * cndd1) * Si / Q1;

	  bi = -ebrt * cndd1 * (1.0 - 1.0 / Q1) 
			- (1.0 + ebrt * cndd1 / vst) / Q1;
    }

    return Si;
}

static double Kc(double X, double T, double r, double b, double v) 
{
	double ebrt, st, p2v, n, m, q2u, Su, h2, Si, K, d1, Q2, LHS, RHS, bi, E;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	ebrt = exp((b - r) * T);
	st = sqrt(T);


	/* Calculation of seed value, Si */
	p2v = pow2(v);
	n = 2.0 * b / p2v;
	m = 2.0 * r / p2v;
	q2u = (-(n - 1.0) + sqrt(pow2(n - 1.0) + 4.0 * m)) / 2.0;
	Su = X / (1.0 - (1.0 / q2u));
	h2 = -(b * T + 2.0 * v * st) * X / (Su - X);
	Si = X + (Su - X) * (1.0 - exp(h2));

	K = 2.0 * r / (p2v * (1.0 - exp(-r * T)));
	d1 = (log(Si / X) + (b + p2v / 2.0) * T) / (v * st);
	Q2 = (-(n - 1.0) + sqrt(pow2(n - 1.0) + 4.0 * K)) / 2.0;
	LHS = Si - X;
	RHS = gbs_call(Si, X, T, r, b, v) + (1.0 - ebrt * cnd(d1)) * Si / Q2;
	bi = ebrt * cnd(d1) * (1.0 - 1.0 / Q2) + (1.0 - ebrt * cnd(d1) / (v * st)) / Q2;

	E = 0.000001;

	/* Newton Raphson algorithm for finding critical price Si */
	while(fabs(LHS - RHS) / X > E) {
	  Si = (X + RHS - bi * Si) / (1.0 - bi);
	  d1 = (log(Si / X) + (b + p2v / 2.0) * T) / (v * st);
	  LHS = Si - X;
	  RHS = gbs_call(Si, X, T, r, b, v) + (1.0 - ebrt * cnd(d1)) * Si / Q2;

	  bi = ebrt * cnd(d1) * (1.0 - (1.0 / Q2)) 
			+ (1.0 - ebrt * normdist(d1) / (v * st)) / Q2;
	}

	assert(is_sane(Si));
	return Si;
}

/* American call */
static double BAWAmericanCallApprox(
	double S,
	double X,
	double T,
	double r,
	double b,
	double v) 
{
	double result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	if(b >= r)  {
	  result = gbs_call(S, X, T, r, b, v);
	} else {
	  const double p2v = pow2(v);
	  const double Sk = Kc(X, T, r, b, v);
	  const double n = 2.0 * b / p2v;
	  const double K = 2.0 * r / (p2v * (1.0 - exp(-r * T)));
	  const double d1 = (log(Sk / X) + (b + p2v / 2.0) * T) / (v * sqrt(T));
	  const double Q2 = (-(n - 1.0) + sqrt(pow2(n - 1.0) + 4.0 * K)) / 2.0;
	  const double a2 = (Sk / Q2) * (1.0 - exp((b - r) * T) * cnd(d1));

	  if(S < Sk) {
	    result = gbs_call(S, X, T, r, b, v) + a2 * pow((S / Sk), Q2);
	  } else {
	    result = S - X;
	  }
	}

	assert(is_sane(result));
	return result;
}

/* American put */
static double BAWAmericanPutApprox(
	double S,
	double X,
	double T,
	double r,
	double b,
	double v) 
{
	double Sk, result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	Sk = Kp(X, T, r, b, v);
    
	if(S > Sk ) {
	  
	  const double p2v = pow2(v);
	  const double n = 2.0 * b / p2v;
	  const double K = 2.0 * r / (p2v * (1.0 - exp(-r * T)));
	  const double d1 = (log(Sk / X) + (b + p2v / 2.0) * T) / (v * sqrt(T));
	  const double Q1 = (-(n - 1.0) - sqrt(pow2(n - 1.0) + 4.0 * K)) / 2.0;
	  const double a1 = -(Sk / Q1) * (1.0 - exp((b - r) * T) * cnd(-d1));
	  result = gbs_put(S, X, T, r, b, v) + a1 * pow((S / Sk), Q1);
	} else {
	  result = X - S;
	}
    
	assert(is_sane(result));
	return result;
}

/* The Barone-Adesi and Whaley (1987) American approximation */
double BAWAmericanApprox(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v) 
{
	double result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	if(fCall) {
		result = BAWAmericanCallApprox(S, X, T, r, b, v);
	} else { 
		result = BAWAmericanPutApprox(S, X, T, r, b, v);
	}
    
	assert(is_sane(result));
	return result;
}

#ifdef BAWAMERICANAPPROX_CHECK
#include <stdlib.h>
#include <stdio.h>

static void report(double computed, double fasit, double t, double v, int baw)
{
	static int has_reported;
	double diff = computed - fasit;

	if(fabs(diff) > 0.001) {
		if(!has_reported) {
			printf("\n   A difference between the numbers in the book and the computed value has been found.\n");
			has_reported = 1;
		}

		printf("   (baw)Time %.2f Vol: %.2f Price %3d Book: %-10.6f Computer: %-10.6f Diff: %.6f\n",
			t, v, baw, fasit, computed, diff);
	}
}


static void report76(double computed, double fasit, double t, double v, int baw)
{
	static int has_reported;
	double diff = computed - fasit;

	if(fabs(diff) > 0.001) {
		if(!has_reported) {
			printf("\n   A difference between the numbers in the book and the computed value has been found.\n");
			has_reported = 1;
		}

		printf("(b76)Time %.2f Vol: %.2f Price %3d Book: %-10.6f Computer: %-10.6f Diff: %.6f\n",
			t, v, baw, fasit, computed, diff);
	}
}

void check_BAWAmericanApprox(void)
{
	/* This array contains values for puts&calls with different 
	 * price of underlying, different volatility and different time to expiry.
	 * It also contains values for both black76 and the 
	 * "Barone-Adesi and Whales", BAW, formula for american options.
	 *
	 * Strike (X) is always 100, risk free interest is always 0.10 (10%) and
	 * cost of carry is always 0.
	 * The table is from page 24 in E.G. Haugs book.
	 */
	struct putcall_value {
		double t, v, baw90, baw100, baw110, b90, b100, b110;
	};

	struct putcall_value putvalues[] = {
		{ 0.1, 0.15, 10.0000, 1.8770, 0.0410,  9.9210, 1.8734, 0.0408 },
		{ 0.1, 0.25, 10.2533, 3.1277, 0.4562, 10.2155, 3.1217, 0.4551 },
		{ 0.1, 0.35, 10.8787, 4.3777, 1.2402, 10.8479, 4.3693, 1.2376 },
		{ 0.5, 0.15, 10.5595, 4.0842, 1.0822, 10.3192, 4.0232, 1.0646 },
		{ 0.5, 0.25, 12.4419, 6.8014, 3.3226, 12.2149, 6.6997, 3.2734 },
		{ 0.5, 0.35, 14.6945, 9.5104, 5.8823, 14.4452, 9.3679, 5.7963 },
	};

	struct putcall_value callvalues[] = {
		{ 0.1, 0.15, 0.0206, 1.8771, 10.0089, 0.0205, 1.8734,  9.9413 },
		{ 0.1, 0.25, 0.3159, 3.1280, 10.3919, 0.3150, 3.1217, 10.3556 },
		{ 0.1, 0.35, 0.9495, 4.3777, 11.1679, 0.9474, 4.3693, 11.1381 },
		{ 0.5, 0.15, 0.8208, 4.0842, 10.8087, 0.8069, 4.0232, 10.5769 },
		{ 0.5, 0.25, 2.7437, 6.8015, 13.0170, 2.7026, 6.6997, 12.7857 },
		{ 0.5, 0.35, 5.0063, 9.5106, 15.5689, 4.9329, 9.3679, 15.3080 },
	};

	size_t i, nelem = sizeof(putvalues) / sizeof(putvalues[0]);
	double r = 0.10, b = 0.00;
	double ta, baw, b76;

	for(i = 0; i < nelem; i++) {

		baw = BAWAmericanApprox(0, 90.0, 100.0, putvalues[i].t, r, b, putvalues[i].v);
		ta = putvalues[i].baw90;
		report(baw, ta, putvalues[i].t, putvalues[i].v, 90);
		assert_equal(baw, putvalues[i].baw90); 

		baw = BAWAmericanApprox(0, 100.0, 100.0, putvalues[i].t, r, b, putvalues[i].v);
		ta = putvalues[i].baw100;
		report(baw, ta, putvalues[i].t, putvalues[i].v, 100);
		assert_equal(baw, putvalues[i].baw100); 

		baw = BAWAmericanApprox(0, 110.0, 100.0, putvalues[i].t, r, b, putvalues[i].v);
		ta = putvalues[i].baw110;
		report(baw, ta, putvalues[i].t, putvalues[i].v, 110);
		assert_equal(baw, putvalues[i].baw110); 

		b76 = black76(0, 90.0, 100.0, putvalues[i].t, r, putvalues[i].v);
		ta = putvalues[i].b90;
		report76(b76, ta, putvalues[i].t, putvalues[i].v, 90);
		assert_equal(b76, putvalues[i].b90); 

		b76 = black76(0, 100.0, 100.0, putvalues[i].t, r, putvalues[i].v);
		ta = putvalues[i].b100;
		report76(b76, ta, putvalues[i].t, putvalues[i].v, 100);
		assert_equal(b76, putvalues[i].b100); 

		b76 = black76(0, 110.0, 100.0, putvalues[i].t, r, putvalues[i].v);
		ta = putvalues[i].b110;
		report76(b76, ta, putvalues[i].t, putvalues[i].v, 110);
		assert_equal(b76, putvalues[i].b110); 

		b76 = black76_put(90.0, 100.0, putvalues[i].t, r, putvalues[i].v);
		ta = putvalues[i].b90;
		report76(b76, ta, putvalues[i].t, putvalues[i].v, 90);
		assert_equal(b76, putvalues[i].b90); 

		b76 = black76_put(100.0, 100.0, putvalues[i].t, r, putvalues[i].v);
		ta = putvalues[i].b100;
		report76(b76, ta, putvalues[i].t, putvalues[i].v, 100);
		assert_equal(b76, putvalues[i].b100); 

		b76 = black76_put(110.0, 100.0, putvalues[i].t, r, putvalues[i].v);
		ta = putvalues[i].b110;
		report76(b76, ta, putvalues[i].t, putvalues[i].v, 110);
		assert_equal(b76, putvalues[i].b110); 

	}

	nelem = sizeof(callvalues) / sizeof(callvalues[0]);
	for(i = 0; i < nelem; i++) {
		baw = BAWAmericanApprox(1, 90.0, 100.0, callvalues[i].t, r, b, callvalues[i].v);
		ta = callvalues[i].baw90;
		report(baw, ta, callvalues[i].t, callvalues[i].v, 90);
		assert_equal(baw, callvalues[i].baw90); 

		baw = BAWAmericanApprox(1, 100.0, 100.0, callvalues[i].t, r, b, callvalues[i].v);
		ta = callvalues[i].baw100;
		report(baw, ta, callvalues[i].t, callvalues[i].v, 100);
		assert_equal(baw, callvalues[i].baw100); 

		baw = BAWAmericanApprox(1, 110.0, 100.0, callvalues[i].t, r, b, callvalues[i].v);
		ta = callvalues[i].baw110;
		report(baw, ta, callvalues[i].t, callvalues[i].v, 110);
		/*assert_equal(baw, callvalues[i].baw110); */

		b76 = black76(1, 90.0, 100.0, callvalues[i].t, r, callvalues[i].v);
		ta = callvalues[i].b90;
		report76(b76, ta, callvalues[i].t, callvalues[i].v, 90);
		assert_equal(b76, callvalues[i].b90); 

		b76 = black76(1, 100.0, 100.0, callvalues[i].t, r, callvalues[i].v);
		ta = callvalues[i].b100;
		report76(b76, ta, callvalues[i].t, callvalues[i].v, 100);
		assert_equal(b76, callvalues[i].b100); 

		b76 = black76(1, 110.0, 100.0, callvalues[i].t, r, callvalues[i].v);
		ta = callvalues[i].b110;
		report76(b76, ta, callvalues[i].t, callvalues[i].v, 110);
		assert_equal(b76, callvalues[i].b110); 

		b76 = black76_call(90.0, 100.0, callvalues[i].t, r, callvalues[i].v);
		ta = callvalues[i].b90;
		report76(b76, ta, callvalues[i].t, callvalues[i].v, 90);
		assert_equal(b76, callvalues[i].b90); 

		b76 = black76_call(100.0, 100.0, callvalues[i].t, r, callvalues[i].v);
		ta = callvalues[i].b100;
		report76(b76, ta, callvalues[i].t, callvalues[i].v, 100);
		assert_equal(b76, callvalues[i].b100); 

		b76 = black76_call(110.0, 100.0, callvalues[i].t, r, callvalues[i].v);
		ta = callvalues[i].b110;
		report76(b76, ta, callvalues[i].t, callvalues[i].v, 110);
		assert_equal(b76, callvalues[i].b110); 
	}
}

int main(void)
{
	check_BAWAmericanApprox();
	return 0;
}


#endif

