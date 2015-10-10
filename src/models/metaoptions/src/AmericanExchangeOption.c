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

/* American option to exchange one asset for another */
double AmericanExchangeOption(
	int fCall,
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
    const double result = BSAmericanApprox(fCall, Q1 * S1, Q2 * S2, T, r - b2, b1 - b2, v);
	assert(is_sane(result));
	return result;
}

#ifdef AMERICANEXCHANGEOPTION_CHECK

static void check_AmericanExchangeOption(void)
{
	double S1 = 22.0, S2 = 20.0, Q1 = 1.0, Q2 = 1.0, r = 0.10, b1 = 0.04, b2 = 0.06, v1 = 0.20;

	/* We have two T's, 0.1 and 0.5. We also have a second v and
	 * three different Rho's. */
	double values[3][2][3] = { 
		{ { 2.1357, 2.0592, 2.0001 }, { 2.8051, 2.5282, 2.2053 } },
		{ { 2.2074, 2.1032, 2.0110 }, { 3.0288, 2.6945, 2.2906 } },
		{ { 2.2902, 2.1618, 2.0359 }, { 3.2664, 2.8893, 2.4261 } }
	};

	double T, v2, Rho;
	size_t iT, iv2, irho;
	int fCall = 1;

	for(iv2 = 0, v2 = 0.15; iv2 < 3; iv2++, v2 += 0.05) {
		for(iT = 0, T = 0.1; iT < 2; iT++, T += 0.4) {
			for(irho = 0, Rho = -0.5; irho < 3; irho++, Rho += 0.5) {
				double computed, fasit = values[iv2][iT][irho];
				computed = AmericanExchangeOption(fCall, S1, S2, Q1, Q2, T, r, b1, b2, v1, v2, Rho);
				assert_equal(computed, fasit);
			}
		}
	}
}


int main(void)
{
	check_AmericanExchangeOption();
	printf("Mangler data for puts\n");
	return 0;
}
#endif

