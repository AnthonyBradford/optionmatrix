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

/* Performance notes:
 * Calls/sec	Action
 * 1.500.000	Added vsT variable+minor cleanup
 * 1.500.000	
 */

/* European option to exchange one asset for another */
double  EuropeanExchangeOption(
	double S1,
	double S2,
	double Q1,
	double Q2,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho) 
{
    const double v = sqrt(pow2(v1) + pow2(v2) - 2.0 * Rho * v1 * v2);
	const double vsT = v * sqrt(T);
    const double d1 = (log(Q1 * S1 / (Q2 * S2)) + (b1 - b2 + pow2(v) / 2.0) * T) / vsT;
    const double d2 = d1 - vsT;
 
    return Q1 * S1 * exp((b1 - r) * T) * cnd(d1) - Q2 * S2 * exp((b2 - r) * T) * cnd(d2);
}

#ifdef EUROPEANEXCHANGEOPTION_CHECK

/* Test-function is more or less equal to AmericanExchangeOption */
void check_EuropeanExchangeOption(void)
{
	double S1 = 22.0, S2 = 20.0, Q1 = 1.0, Q2 = 1.0, r = 0.10, b1 = 0.04, b2 = 0.06, v1 = 0.20;
	/* We have data for a combination of three Rho's, two T's and 3 volatility values */
	double values[3][2][3] = {
		{{2.1251, 2.0446, 1.9736}, {2.7619, 2.4793, 2.1378}},
		{{2.1986, 2.0913, 1.9891}, {2.9881, 2.6496, 2.2306}},
		{{2.2827, 2.1520, 2.0189}, {3.2272, 2.8472, 2.3736}}
	};

	double T, v2, Rho;
	size_t iT, iv2, iRho;

	for(iv2 = 0, v2 = 0.15; iv2 < 3; iv2++, v2 += 0.05) {
		for(iT = 0, T = 0.1; iT < 2; iT++, T += 0.4) {
			for(iRho = 0, Rho = -0.5; iRho < 3; iRho++, Rho += 0.5) {
				double computed, fasit = values[iv2][iT][iRho];
				computed = EuropeanExchangeOption(S1, S2, Q1, Q2, T, r, b1, b2, v1, v2, Rho);
				assert_equal(computed, fasit);
			}
		}
	}
}

int main(void)
{
	check_EuropeanExchangeOption();
	return 0;
}
#endif

