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


/* Partial-time singel asset barrier options */
double PartialTimeBarrier(
	const char* TypeFlag,
	double S,
	double X,
	double H,
	double t1,
	double T2,
	double r,
	double b,
	double v) 
{
	int eta;
	double hs, vv, vv2, sT2, vsT2, d1, d2, f1, f2, e1, e2, e3,
		e4, mu, Rho, g1, g2, g3, g4, z1, z2, z3, z4, z5, z6, z7, z8,
		result;

	assert_valid_price(S);
	assert_valid_strike(X);
	assert_valid_time(t1);
	assert_valid_time(T2);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

    if (!strcmp(TypeFlag, "cdoA")) 
        eta = 1;
	else if(!strcmp(TypeFlag, "cuoA")) 
        eta = -1;
	else
		abort();
    
	hs = H/S;
	vv = v*v;
	vv2 = vv / 2.0;
	sT2 = sqrt(T2);
	vsT2 = v * sT2;

    d1 = (log(S / X) + (b + vv2) * T2) / vsT2;
    d2 = d1 - vsT2;
    f1 = (log(S / X) + 2.0 * log(hs) + (b + vv2) * T2) / vsT2;
    f2 = f1 - vsT2;
    e1 = (log(S / H) + (b + vv2) * t1) / (v * sqrt(t1));
    e2 = e1 - v * sqrt(t1);
    e3 = e1 + 2.0 * log(hs) / (v * sqrt(t1));
    e4 = e3 - v * sqrt(t1);
    mu = (b - vv2) / vv;
    Rho = sqrt(t1 / T2);
    g1 = (log(S / H) + (b + vv2) * T2) / vsT2;
    g2 = g1 - vsT2;
    g3 = g1 + 2.0 * log(hs) / (vsT2);
    g4 = g3 - vsT2;
    
    z1 = cnd(e2) - pow(hs, (2.0 * mu)) * cnd(e4);
    z2 = cnd(-e2) - pow(hs, (2.0 * mu)) * cnd(-e4);
    z3 = cbnd(g2, e2, Rho) - pow(hs, (2.0 * mu)) * cbnd(g4, -e4, -Rho);
    z4 = cbnd(-g2, -e2, Rho) - pow(hs, (2.0 * mu)) * cbnd(-g4, e4, -Rho);
    z5 = cnd(e1) - pow(hs, (2.0 * (mu + 1.0))) * cnd(e3);
    z6 = cnd(-e1) - pow(hs, (2.0 * (mu + 1.0))) * cnd(-e3);
    z7 = cbnd(g1, e1, Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(g3, -e3, -Rho);
    z8 = cbnd(-g1, -e1, Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(-g3, e3, -Rho);
    
    if (!strcmp(TypeFlag, "cdoA") || !strcmp(TypeFlag, "cuoA")) { /* call down-and out and up-and-out type A */
        result 
			= S * exp((b - r) * T2) * (cbnd(d1, eta * e1, eta * Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(f1, eta * e3, eta * Rho)) 
			- X * exp(-r * T2)      * (cbnd(d2, eta * e2, eta * Rho) - pow(hs, (2.0 * mu))       * cbnd(f2, eta * e4, eta * Rho));
    }
	else if( !strcmp(TypeFlag, "cdoB2") && X < H) {  /* call down-and-out type B2 */
        result 
			= S * exp((b - r) * T2) * (cbnd(g1, e1, Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(g3, -e3, -Rho)) 
			- X * exp(-r * T2)      * (cbnd(g2, e2, Rho) - pow(hs, (2.0 * mu))       * cbnd(g4, -e4, -Rho));
    }
	else if( !strcmp(TypeFlag, "cdoB2") && X > H) {
        result = PartialTimeBarrier("coB1", S, X, H, t1, T2, r, b, v);
    }
	else if( !strcmp(TypeFlag, "cuoB2") && X < H) {  /* call up-and-out type B2 */
        result 
			= S * exp((b - r) * T2) * (cbnd(-g1, -e1, Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(-g3, e3, -Rho)) 
			- X * exp(-r * T2)      * (cbnd(-g2, -e2, Rho) - pow(hs, (2.0 * mu))       * cbnd(-g4, e4, -Rho)) 
			- S * exp((b - r) * T2) * (cbnd(-d1, -e1, Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(e3, -f1, -Rho)) 
			+ X * exp(-r * T2)      * (cbnd(-d2, -e2, Rho) - pow(hs, (2.0 * mu))       * cbnd(e4, -f2, -Rho));
    }
	else if( !strcmp(TypeFlag, "coB1") && X > H) {  /* call out type B1 */
        result 
			= S * exp((b - r) * T2) 
			* (cbnd(d1, e1, Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(f1, -e3, -Rho)) 
			- X * exp(-r * T2) 
			* (cbnd(d2, e2, Rho) - pow(hs, (2.0 * mu)) * cbnd(f2, -e4, -Rho));
    }
	else if( !strcmp(TypeFlag, "coB1") && X < H) {
        result 
			= S * exp((b - r) * T2) * (cbnd(-g1, -e1, Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(-g3, e3, -Rho)) 
			- X * exp(-r * T2)      * (cbnd(-g2, -e2, Rho) - pow(hs, (2.0 * mu))       * cbnd(-g4, e4, -Rho)) 
			- S * exp((b - r) * T2) * (cbnd(-d1, -e1, Rho) - pow(hs, (2.0 * (mu + 1.0))) * cbnd(-f1, e3, -Rho)) 
			+ X * exp(-r * T2)      * (cbnd(-d2, -e2, Rho) - pow(hs, (2.0 * mu))       * cbnd(-f2, e4, -Rho)) 
			+ S * exp((b - r) * T2) * (cbnd(g1, e1, Rho)   - pow(hs, (2.0 * (mu + 1.0))) * cbnd(g3, -e3, -Rho)) 
			- X * exp(-r * T2)      * (cbnd(g2, e2, Rho)   - pow(hs, (2.0 * mu))       * cbnd(g4, -e4, -Rho));
    }
	else if( !strcmp(TypeFlag, "pdoA")) {  /* put down-and out and up-and-out type A */
        result = PartialTimeBarrier("cdoA", S, X, H, t1, T2, r, b, v) - S * exp((b - r) * T2) * z5 + X * exp(-r * T2) * z1;
    }
	else if( !strcmp(TypeFlag, "puoA")) {
        result = PartialTimeBarrier("cuoA", S, X, H, t1, T2, r, b, v) - S * exp((b - r) * T2) * z6 + X * exp(-r * T2) * z2;
    }
	else if( !strcmp(TypeFlag, "poB1")) {  /* put out type B1 */
        result = PartialTimeBarrier("coB1", S, X, H, t1, T2, r, b, v) - S * exp((b - r) * T2) * z8 + X * exp(-r * T2) * z4 - S * exp((b - r) * T2) * z7 + X * exp(-r * T2) * z3;
    }
	else if( !strcmp(TypeFlag, "pdoB2")) {  /* put down-and-out type B2 */
        result = PartialTimeBarrier("cdoB2", S, X, H, t1, T2, r, b, v) - S * exp((b - r) * T2) * z7 + X * exp(-r * T2) * z3;
    }
	else if( !strcmp(TypeFlag, "puoB2")) {  /* put up-and-out type B2 */
        result = PartialTimeBarrier("cuoB2", S, X, H, t1, T2, r, b, v) - S * exp((b - r) * T2) * z8 + X * exp(-r * T2) * z4;
    }
	else
		abort();

	assert(is_sane(result));
	return result;
}

#ifdef PARTIALTIMEBARRIER_CHECK
void check_PartialTimeBarrier(void)
{
	printf("	%s(): Not implemented\n", __func__);
}

int main(void)
{
	check_PartialTimeBarrier();
	return 77;
}
#endif

