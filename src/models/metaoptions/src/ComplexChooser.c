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

/* Critical value complex chooser option */
static double CriticalValueChooser(
	double S,
	double Xc,
	double Xp,
	double T, 
	double Tc,
	double Tp,
	double r,
	double b,
	double v) 
{
	double Sv, ci, Pi, dc, dp, yi, di;
    const double epsilon = 0.001;

	assert_valid_price(S);
	assert_valid_time(T);

    Sv = S;
    
    ci = gbs_call(Sv, Xc, Tc - T, r, b, v);
    Pi = gbs_put (Sv, Xp, Tp - T, r, b, v);

    dc = delta_call(Sv, Xc, Tc - T, r, b, v);
    dp = delta_put (Sv, Xp, Tp - T, r, b, v);

    yi = ci - Pi;
    di = dc - dp;

    /* Newton-Raphson search process */
    while (fabs(yi) > epsilon) {
        Sv = Sv - (yi) / di;

        ci = gbs_call(Sv, Xc, Tc - T, r, b, v);
        Pi = gbs_put (Sv, Xp, Tp - T, r, b, v);

        dc = delta_call(Sv, Xc, Tc - T, r, b, v);
        dp = delta_put (Sv, Xp, Tp - T, r, b, v);

        yi = ci - Pi;
        di = dc - dp;
    }

    return Sv;
}

/* Complex chooser options */
double ComplexChooser(
	double S,
	double Xc,
	double Xp,
	double T,
	double Tc, 
	double Tp,
	double r,
	double b,
	double v) 
{
	assert_valid_price(S);
	assert_valid_strike(Xc);
	assert_valid_strike(Xp);
	assert_valid_time(Tc);
	assert_valid_time(Tp);
	assert_valid_interest_rate(r);
	assert_valid_cost_of_carry(b);
	assert_valid_volatility(v);

	{ /* No C99 */

	const double vsT = v * sqrt(T);
	const double vsTc = v * sqrt(Tc);
	const double vsTp = v * sqrt(Tp);
	const double bv2 = b + pow2(v)/2.0;

    const double I = CriticalValueChooser(S, Xc, Xp, T, Tc, Tp, r, b, v);
    const double d1 = (log(S / I) + bv2 * T) / vsT;
    const double d2 = d1 - vsT;
    const double Y1 = (log(S / Xc) + bv2 * Tc) / vsTc;
    const double y2 = (log(S / Xp) + bv2 * Tp) / vsTp;
    const double rho1 = sqrt(T / Tc);
    const double rho2 = sqrt(T / Tp);
    
    const double result 
		=  S * exp((b - r) * Tc) * cbnd(d1, Y1, rho1) 
		- Xc * exp(-r * Tc)      * cbnd(d2, Y1 - vsTc, rho1) 
		-  S * exp((b - r) * Tp) * cbnd(-d1, -y2, rho2) 
		+ Xp * exp(-r * Tp)      * cbnd(-d2, -y2 + vsTp, rho2);

	return result;
	} /* No C99 */
}

#ifdef COMPLEXCHOOSER_CHECK
void check_ComplexChooser(void)
{
	double S = 50, Xc = 55.0, Xp = 48.0, Tc = 0.5, Tp = 0.5833, T = 0.25, r = 0.10, b = 0.05, v = 0.35;

	assert_equal(ComplexChooser(S, Xc, Xp, T, Tc, Tp, r, b, v), 6.0508);
}


int main(void)
{
	check_ComplexChooser();
	return 0;
}
#endif

