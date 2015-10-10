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


/* Forward start options */
double ForwardStartOption(
	int fCall,
	double S,
	double alpha,
	double t1,
	double T,
	double r,
	double b,
	double v)
{
	double result;

	assert_valid_price(S);
	assert_valid_time(T);

    result = S * exp((b - r) * t1) * gbs(fCall, 1.0, alpha, T - t1, r, b, v);
	assert(is_sane(result));
	return result;
}

#ifdef FORWARDSTARTOPTION_CHECK

static void check_ForwardStartOption(void)
{
	/* ForwardStartOption, page 37 */
	double S = 60, T = 1.0, r = 0.08, b = 0.08 - 0.04, v = 0.30;
	double t = 0.25, alpha = 1.1;

	double computed = ForwardStartOption(1, S, alpha, t, T, r, b, v);
	assert_equal(computed, 4.4064);
}

int main(void)
{
	check_ForwardStartOption();
	return 0;
}

#endif

