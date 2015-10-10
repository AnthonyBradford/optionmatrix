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

#include <stdlib.h>
#include <math.h>

#include "metaoptions.h"

/* Convertible bonds in binomial trees */
extern double ConvertibleBond(
	int EuropeanOption,
	double S,
	double X,
	double T2,
	double t1,
	double r,
	double k,
	double q,
	double v,
	double F,
	double Coupon,
	int n)
{
	double result, CRatio, dt, u, d, p, StockPrice, Time, CouponTime;
	double CouponValue;
	int i, j, CouponPayment;

	double *OptionValue;	/* Option Value at each node */
	double *convprob; /* Conversion probability at each node */

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);
	assert(n > 0);

	if( (OptionValue = calloc(n + 1, sizeof *OptionValue)) == NULL
	||  ( convprob = calloc(n + 1, sizeof *convprob)) == NULL) {
		abort();
	}



	CRatio = F / X; /*Conversion Ratio= FaceValue/Strike */
	dt = T2 / n;
	u = exp(v * sqrt(dt));
	d = 1.0 / u;
	p =(exp((r - q) * dt) - d) / (u - d);

	for(i = 0; i <= n; i++) {
		StockPrice = S * pow(u, (double)i) * pow(d, (double)(n - i));
		OptionValue[i] = fmax(F + Coupon, CRatio * StockPrice);
		if(OptionValue[i] == F + Coupon) 
			convprob[i] = 0;
		else
			convprob[i] = 1;

	}

	Time = 0.0;
	CouponTime = T2;
	for(j = n - 1; j >= 0; j--) {
		if(CouponTime != T2 - (int)((n - j) * dt)) {
			CouponPayment = 1;
			CouponTime = T2 - (int)((n - j) * dt);
			Time = CouponTime - dt * j;
		}
		else {
			CouponPayment = 0;
		}

		for(i = 0; i <= j; i++) {
			const double ru = convprob[i + 1] * r +(1 - convprob[i + 1]) * (r + k);
			const double rd = convprob[i] * r +(1 - convprob[i]) * (r + k);
			StockPrice = S * pow(u, (double)i) * pow(d, (double)abs(i - j));

			if(CouponPayment == 1) {
				CouponValue = Coupon * (p * exp(-ru * Time) + (1 - p) * exp(-rd * Time));
			}
			else 
				CouponValue = 0;

			if(EuropeanOption || (!EuropeanOption && dt * j <= t1)) {
				OptionValue[i] 
					= CouponValue 
					+ p * OptionValue[i + 1] * exp(-ru * dt) 
					+ (1 - p) * OptionValue[i] * exp(-rd * dt);

				convprob[i] = p * convprob[i + 1] + (1 - p) * convprob[i] ;
			}
			else if(!EuropeanOption) {
				double d1 = CRatio *(StockPrice - X) + F;
				double d2 
					= CouponValue + p * OptionValue[i + 1] * exp(-ru * dt) 
					+ (1 - p) * OptionValue[i] * exp(-rd * dt);

				OptionValue[i] = fmax(d1, d2);

				if(OptionValue[i] == CRatio * (StockPrice - X) + F) 
					convprob[i] = 1;
				else
					convprob[i] = p * convprob[i + 1] + (1 - p) * convprob[i];
			}
		}
	}

	result = OptionValue[0];
	assert(is_sane(result));

	free(OptionValue);
	free(convprob);
	return result;
}

